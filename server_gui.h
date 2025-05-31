#ifndef SERVER_GUI_H
#define SERVER_GUI_H

#include <QMainWindow>
#include <QTableWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

class ServerGUI : public QMainWindow {
    Q_OBJECT

public:
    explicit ServerGUI(QWidget *parent = nullptr);
    ~ServerGUI();

private slots:
    void refreshMessages();
    void refreshUsers();
    void banUser();
    void disconnectUser();

private:
    // UI элементы
    QWidget *centralWidget;
    
    // Таблица сообщений
    QTableWidget *messagesTable;
    
    // Список пользователей
    QListWidget *usersList;
    
    // Кнопки управления пользователями
    QPushButton *banButton;
    QPushButton *disconnectButton;
    
    // Методы для обновления данных
    void loadMessages();
    void loadUsers();

    // Внутренние данные (имитация базы данных)
    // В реальности сюда подключается к Postgres через QtSql или другой драйвер
};

#endif // SERVER_GUI_H
