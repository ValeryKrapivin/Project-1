This project is a graphical interface for server management, implemented using Qt.
The interface allows you to view a list of users and messages, as well as perform actions - ban and disconnect users.
The project uses simulated data, which allows you to test the interface without connecting to a real database.
Project structure
main.cpp — entry point to the application, creates and displays the main window.
server_gui.h — declaration of the ServerGUI class, responsible for the interface.
server_gui.cpp — implementation of the ServerGUI class methods, interface setup and event handling logic.
Main interface components
User list (QListWidget)
Message table (QTableWidget)
User management buttons:
"Ban User" — block the selected user
"Disconnect User" — disconnect the selected user
"Refresh Messages" — refresh the message list
Functionality
Simulation of user and message data (in reality, connection to a database or API)
Updating lists by buttons
Ability to select a user and apply actions (ban/disable)
