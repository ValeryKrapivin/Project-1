#include "server_gui.h"
#include <QHeaderView>
#include <QDebug>

// Имитация данных (в реальности подключение к базе данных)
struct Message {
    int id;
    QString sender;
    QString recipient; // пустая строка для публичных сообщений
    QString content;
};

struct User {
    int id;
    QString username;
    bool isBanned;
};

QVector<Message> messages = {
    {1, "Alice", "", "Hello everyone!"},
    {2, "Bob", "Alice", "Hi Alice!"},
    {3, "Charlie", "", "Good morning!"},
};

QVector<User> users = {
    {1, "Alice", false},
    {2, "Bob", false},
    {3, "Charlie", false},
};

ServerGUI::ServerGUI(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Server Management");
    resize(800, 600);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Создаем layout
    auto mainLayout = new QHBoxLayout(centralWidget);

    // Левая часть: список пользователей и кнопки
    auto leftLayout = new QVBoxLayout();

    usersList = new QListWidget();
    loadUsers();

    banButton = new QPushButton("Ban User");
    disconnectButton = new QPushButton("Disconnect User");
    
    connect(banButton, &QPushButton::clicked, this, &ServerGUI::banUser);
        connect(disconnectButton, &QPushButton::clicked, this, &ServerGUI::disconnectUser);

        leftLayout->addWidget(usersList);
        leftLayout->addWidget(banButton);
        leftLayout->addWidget(disconnectButton);

        // Правая часть: таблица сообщений и обновление
        auto rightLayout = new QVBoxLayout();

        messagesTable = new QTableWidget();
        messagesTable->setColumnCount(4);
        QStringList headers = {"ID", "Sender", "Recipient", "Content"};
        messagesTable->setHorizontalHeaderLabels(headers);
        messagesTable->horizontalHeader()->setStretchLastSection(true);
        loadMessages();

        auto refreshBtn = new QPushButton("Refresh Messages");
        connect(refreshBtn, &QPushButton::clicked, this, &ServerGUI::refreshMessages);

        rightLayout->addWidget(messagesTable);
        rightLayout->addWidget(refreshBtn);

        mainLayout->addLayout(leftLayout, 1);
        mainLayout->addLayout(rightLayout, 3);
}

ServerGUI::~ServerGUI() {}

void ServerGUI::loadMessages() {
    messagesTable->setRowCount(0);
    
    for (const auto &msg : messages) {
        int row = messagesTable->rowCount();
        messagesTable->insertRow(row);
        
        messagesTable->setItem(row, 0, new QTableWidgetItem(QString::number(msg.id)));
        messagesTable->setItem(row, 1, new QTableWidgetItem(msg.sender));
        messagesTable->setItem(row, 2, new QTableWidgetItem(msg.recipient));
        messagesTable->setItem(row, 3, new QTableWidgetItem(msg.content));
        
        // Можно добавить цвет или стиль для приватных сообщений
        if (!msg.recipient.isEmpty()) {
            for (int col=0; col<4; ++col) {
                auto item = messagesTable->item(row,col);
                item->setBackground(Qt::lightGray);
            }
        }
        
        // Можно добавить возможность редактирования или удаления сообщений по необходимости
     }
}

void ServerGUI::loadUsers() {
     usersList->clear();
     for (const auto &user : users) {
         QString displayName = user.username + (user.isBanned ? " [BANNED]" : "");
         QListWidgetItem *item = new QListWidgetItem(displayName);
         item->setData(Qt::UserRole, user.id);
         if (user.isBanned) {
             item->setForeground(Qt::red);
         }
         usersList->addItem(item);
     }
}

void ServerGUI::refreshMessages() {
     loadMessages();
}

void ServerGUI::refreshUsers() {
     loadUsers();
}

void ServerGUI::banUser() {
     auto selectedItems = usersList->selectedItems();
     if (selectedItems.isEmpty()) {
         QMessageBox::warning(this,"Warning","Select a user to ban");
         return;
     }
     auto item = selectedItems.first();
     int userId = item->data(Qt::UserRole).toInt();

     for (auto &user : users) {
         if (user.id == userId) {
             user.isBanned = true;
             break;
         }
     }
     loadUsers();
}

void ServerGUI::disconnectUser() {
     auto selectedItems = usersList->selectedItems();
     if (selectedItems.isEmpty()) {
         QMessageBox::warning(this,"Warning","Select a user to disconnect");
         return;
     }
     auto item = selectedItems.first();
     int userId = item->data(Qt::UserRole).toInt();

     QMessageBox::information(this,"Disconnect","User disconnected: ID " + QString::number(userId));
     
     // В реальности тут отправляется команда отключения пользователя на сервере.
}
