#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "notesmodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mNotesModel = new NotesModel(this);
    ui->TblNotes->setModel(mNotesModel);

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
