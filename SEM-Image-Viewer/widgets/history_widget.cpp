#include "history_widget.h"
#include <QToolButton>
#include <QVBoxLayout>

HistoryWidget::HistoryWidget(QWidget *parent)
    : QWidget(parent)
{
    // Create main vertical layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(0);

    // Create a horizontal layout for the header and buttons
    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->setSpacing(5);

    // Create toggle button
    toggleButton = new QToolButton(this);
    toggleButton->setArrowType(Qt::DownArrow);


    // Create header label

    headerLabel = new QLabel("History", this);
    headerLabel->setStyleSheet("font-size: 16px; font-weight: bold; background-color: transparent");
    headerLayout->addWidget(headerLabel);

    // Add a spacer to push buttons to the right
    // Add a spacer to push buttons to the right
    headerLayout->addStretch();

    // Create Undo button with icon
    undoButton = new QPushButton(this);
    undoButton->setObjectName("undoButton");

    headerLayout->addWidget(undoButton);

    // Create Redo button with icon
    // Create Redo button with icon
    redoButton = new QPushButton(this);
    redoButton->setObjectName("redoButton");
    undoButton->setToolTip("Undo");
    redoButton->setToolTip("Redo");
    redoButton->setStyleSheet(
        "QPushButton { "
        "   padding: 2px;"
        "}"
        );
    headerLayout->addWidget(redoButton);
    headerLayout->addWidget(toggleButton);
    // Add header layout to main layout
    mainLayout->addLayout(headerLayout);


    // Create action list
    // Create container for action list with vertical line
    listContainer = new QWidget(this);
    QHBoxLayout* listContainerLayout = new QHBoxLayout(listContainer);
    listContainerLayout->setContentsMargins(0, 5, 0, 0);
    listContainerLayout->setSpacing(0);

    // Add vertical line
    QFrame* line = new QFrame(listContainer);
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Plain);
    line->setStyleSheet("color: #404040;"); // Dark gray line
    listContainerLayout->addWidget(line);

    // Create container for list
    QWidget* listContentContainer = new QWidget(listContainer);
    QVBoxLayout* listContentLayout = new QVBoxLayout(listContentContainer);
    listContentLayout->setContentsMargins(10, 0, 0, 0);
    listContentLayout->setSpacing(0);

    // Create action list
    actionList = new QListWidget(this);
    actionList->setSelectionMode(QAbstractItemView::NoSelection);

    actionList->setStyleSheet(
        "QListWidget {"
        "    background: transparent;" // Makes the background transparent
        "    border: none;"            // Removes the border
        "    outline: none;"           // Removes focus rectangle (optional)
        "}"
        );

    listContentLayout->addWidget(actionList);

    listContainerLayout->addWidget(listContentContainer);
    mainLayout->addWidget(listContainer);

    // Connect buttons to slots
    connect(undoButton, &QPushButton::clicked, this, &HistoryWidget::undoAction);
    connect(redoButton, &QPushButton::clicked, this, &HistoryWidget::redoAction);
    connect(toggleButton,&QToolButton::clicked,this,&HistoryWidget::showAndHideList);
    // Set the main layout
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
}

void HistoryWidget::updateActionList(const QString &action)
{
    actionList->addItem(action);
}

void HistoryWidget::loadActionList(const QList<QString> &actions){

    actionList->clear();


    if(actions.empty()){
        return;
    }
    for (const QString &action : actions)
    {
        actionList->addItem(action);
    }
}
void HistoryWidget::popAction() {
    if (actionList->count() > 0) {
        delete actionList->takeItem(actionList->count() - 1);  // Remove the last item
    }
}
void HistoryWidget::undoAction(){
    emit undo();
}
void HistoryWidget::redoAction(){
    emit redo();
}
void HistoryWidget::showAndHideList(){
    if (toggleButton->arrowType() == Qt::DownArrow) {
        toggleButton->setArrowType(Qt::UpArrow);
        listContainer->hide();
    } else {
        toggleButton->setArrowType(Qt::DownArrow);
        listContainer->show();
    }
}
