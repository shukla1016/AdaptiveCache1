// main_window.cpp
#include "main_window.h"
#include "database_handler.h"
#include "splay_tree.h"
#include <QMessageBox>
#include <QInputDialog>
#include <chrono>
#include <iostream>

const double ALPHA = 0.5;       // For score calculation
const int MAX_CACHE_SIZE = 3;   // Maximum cache size
static long long int global_time = 0;

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent), dbHandler("data.db"), cache(ALPHA, MAX_CACHE_SIZE) {
    ui.setupUi(this);

    // Connect UI actions to their corresponding slots
    connect(ui.searchButton, &QPushButton::clicked, this, &MainWindow::onSearch);
    connect(ui.insertButton, &QPushButton::clicked, this, &MainWindow::onInsert);
    connect(ui.deleteButton, &QPushButton::clicked, this, &MainWindow::onDelete);
    connect(ui.displayCacheButton, &QPushButton::clicked, this, &MainWindow::onDisplayCache);
    connect(ui.exitButton, &QPushButton::clicked, this, &MainWindow::onExit);
}

MainWindow::~MainWindow() {}

void MainWindow::onSearch() {
    bool ok;
    int key = ui.keyInput->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid key!");
        return;
    }

    ui.resultLabel->setText("Searching...");
    QApplication::processEvents();

    auto start = std::chrono::high_resolution_clock::now();
    if (cache.search(key, ++global_time)) {
        auto stop = std::chrono::high_resolution_clock::now();
        std::string value = dbHandler.getValue(key);
        ui.resultLabel->setText(QString::fromStdString("Found in cache: Key=" + std::to_string(key) + ", Value=" + value));
        logTimeElapsed("Cache Search", start, stop);
    } else {
        auto stop = std::chrono::high_resolution_clock::now();
        ui.logTextEdit->setText("Cache Miss");

        ui.resultLabel->setText("Not found in cache. Checking database...");
        QApplication::processEvents();

        start = std::chrono::high_resolution_clock::now();
        std::string value = dbHandler.getValue(key);
        stop = std::chrono::high_resolution_clock::now();

        if (!value.empty()) {
            cache.insert(key, global_time);
            ui.resultLabel->setText(QString::fromStdString("Found in database: Key=" + std::to_string(key) + ", Value=" + value));
        } else {
            ui.resultLabel->setText("Key not found in database!");
        }
        logTimeElapsed("Database Search", start, stop);
    }
}

void MainWindow::onInsert() {
    bool ok;
    int key = ui.keyInput->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid key!");
        return;
    }

    bool valueOk;
    QString value = QInputDialog::getText(this, "Insert Value", "Enter value for key " + QString::number(key), QLineEdit::Normal, "", &valueOk);

    if (valueOk) {
        int a = dbHandler.insertRecord(key, value.toStdString());
        if(a==0)
            ui.resultLabel->setText("Inserted: Key=" + QString::number(key) + ", Value=" + value);
        else
            ui.resultLabel->setText("Insert failed");
    }
}

void MainWindow::onDelete() {
    bool ok;
    int key = ui.keyInput->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid key!");
        return;
    }

    dbHandler.deleteRecord(key);
    cache.remove(key);
    cache.current_size--;
    ui.resultLabel->setText("Deleted key: " + QString::number(key));
}

void MainWindow::onDisplayCache() {
    if (cache.current_size == 0) {
        ui.resultLabel->setText("Cache is empty!");
    } else {
        std::string cacheContent = cache.toString();
        ui.resultLabel->setText(QString::fromStdString("Cache:\n" + cacheContent));
    }
}

void MainWindow::onExit() {
    QApplication::quit();
}

void MainWindow::logTimeElapsed(const std::string &operation, const std::chrono::high_resolution_clock::time_point &start, const std::chrono::high_resolution_clock::time_point &stop) {
    // Calculate the duration in microseconds
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    
    // Log to console
    std::cout << operation << " took " << duration << " microseconds" << std::endl;

    // Log to GUI label
    ui.logTextEdit->setText(QString::fromStdString(operation) + " took " + QString::number(duration) + " microseconds");
}
