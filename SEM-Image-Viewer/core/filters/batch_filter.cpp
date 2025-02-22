#include "batch_filter.h"
#include "../engines/logger.h"
#include "../engines/thread_pool.h"
#include "../engines/workspace.h"

void BatchFilter::apply(std::unique_ptr<ImageFilter> filter, const std::vector<Image*> &input) {
  if (input.empty() || !filter)
    return;

  startTime = QDateTime::currentDateTime();
  
  int progressbarID = Logger::instance()->logMessageWithProgressBar(
      Logger::MessageTypes::info,
      Logger::MessageID::batch_filter_applied,
      Logger::MessageOption::without_path,
      {  },
      input.size()
  );

  Workspace::Instance()->getActiveSession().getImageRepo()._current_operations.fetch_add(1, std::memory_order_relaxed);

  post(ThreadPool::instance(), [this, filter = std::move(filter), input = std::move(input), progressbarID]() {

    std::vector<std::pair<cv::Mat, bool>> output(input.size());
    ImageFilter* filterPtr = filter.get();

    const std::size_t batch_size = 17;

    std::vector<std::future<void>> futures;
    std::atomic_int processed_images = 0;

    for (std::size_t i = 0; i < input.size(); i += batch_size) {
      auto start = input.begin() + i;
      auto end = (i + batch_size < input.size()) ? start + batch_size : input.end();
      std::vector<Image*> batch(start, end);

      auto future = post(ThreadPool::instance(),
          use_future([filterPtr, batch, progressbarID, &output, &processed_images, global_start = i]() {
            for (std::size_t j = 0; j < batch.size(); ++j) {
              std::size_t global_index = global_start + j;
              output[global_index].second = filterPtr->applyFilter(*batch[j], output[global_index].first, false);
              if (!output[global_index].second)
                output[global_index].first = batch[j]->readImageMat();
              processed_images++;
              float progress = static_cast<float>(processed_images) / static_cast<float>(output.size());
              Logger::instance()->updateProgressBar(progressbarID, progress);
            }
          }));
      futures.push_back(std::move(future));
    }

    for (auto& future : futures) {
      future.get();
    }

    Workspace::Instance()->getActiveSession().getImageRepo()._current_operations.fetch_sub(1, std::memory_order_relaxed);

    emit onFinish(input, output, filter->getImageSource());
  });
}
