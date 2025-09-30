#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QMessageBox>

class BasicWindow : public QWidget {
    Q_OBJECT

public:
    BasicWindow(QWidget *parent = nullptr) : QWidget(parent) {
        setWindowTitle("Qt Basic UI Example");
        setFixedSize(400, 300);

        setupUI();
        connectSignals();
    }

private slots:
    void onButtonClicked() {
        QString text = lineEdit->text();
        if (!text.isEmpty()) {
            textEdit->append("You entered: " + text);
            lineEdit->clear();
        } else {
            QMessageBox::warning(this, "Warning", "Please enter some text!");
        }
    }

    void onClearClicked() {
        textEdit->clear();
    }

private:
    void setupUI() {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        QLabel *titleLabel = new QLabel("Qt Basic UI Demo");
        titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2c3e50;");

        QHBoxLayout *inputLayout = new QHBoxLayout();
        QLabel *inputLabel = new QLabel("Enter text:");
        lineEdit = new QLineEdit();
        lineEdit->setPlaceholderText("Type something here...");

        inputLayout->addWidget(inputLabel);
        inputLayout->addWidget(lineEdit);

        QHBoxLayout *buttonLayout = new QHBoxLayout();
        addButton = new QPushButton("Add Text");
        clearButton = new QPushButton("Clear All");

        buttonLayout->addWidget(addButton);
        buttonLayout->addWidget(clearButton);

        textEdit = new QTextEdit();
        textEdit->setReadOnly(true);
        textEdit->setPlaceholderText("Your text entries will appear here...");

        mainLayout->addWidget(titleLabel);
        mainLayout->addLayout(inputLayout);
        mainLayout->addLayout(buttonLayout);
        mainLayout->addWidget(textEdit);
    }

    void connectSignals() {
        connect(addButton, &QPushButton::clicked, this, &BasicWindow::onButtonClicked);
        connect(clearButton, &QPushButton::clicked, this, &BasicWindow::onClearClicked);
        connect(lineEdit, &QLineEdit::returnPressed, this, &BasicWindow::onButtonClicked);
    }

    QLineEdit *lineEdit;
    QPushButton *addButton;
    QPushButton *clearButton;
    QTextEdit *textEdit;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    BasicWindow window;
    window.show();

    return app.exec();
}

#include "main.moc"