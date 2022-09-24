#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "notesmodel.h"
#include "notesprovider.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mNotesModel = new NotesModel(this);
    ui->TblNotes->setModel(mNotesModel);
    ui->TblNotes->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);

    QHeaderView *verticalHeader = ui->TblNotes->verticalHeader();
    verticalHeader->hide();
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(24);

    QHeaderView *horizontalHeader = ui->TblNotes->horizontalHeader();
    horizontalHeader->setSectionResizeMode(QHeaderView::Stretch);

    QTimer* timer = new QTimer(this);
    timer->setSingleShot(false);
    timer->setInterval(3000);

    QObject::connect(timer, &QTimer::timeout, [this]() {
        int count = 1 + rand() % 3;
        QVector<NoteHeader> headers;
        for(int i = 0; i < count; ++i)
        {
            NoteHeader header;
            header.id = 0;
            header.title = "item " + QString::number(mNotesModel->rowCount(QModelIndex()));
            header.createdDateTime = QDateTime::currentDateTime();

            headers << header;
        }

        mNotesModel->insertNotes(rand() % (mNotesModel->rowCount(QModelIndex()) + 1), headers);
    });
    timer->start();

    QTimer* timer2 = new QTimer(this);
    timer2->setSingleShot(false);
    timer2->setInterval(4000);

    QObject::connect(timer2, &QTimer::timeout, [this]() {
        int count = 1 + rand() % 3;
        int row = rand() % mNotesModel->rowCount(QModelIndex());
        bool result = mNotesModel->removeRows(row, count, QModelIndex());
        qDebug() << "remove:" << row << count << result;
    });
    timer2->start();

    connect(ui->BtnNew, &QPushButton::clicked, this, &MainWindow::OnAdd);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnAdd()
{
    int row = mNotesModel->rowCount(QModelIndex());
    mNotesModel->insertRow(row);
    //mNotesModel->setData(mNotesModel->index(row, 0), "New note");
}
