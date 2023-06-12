#include <QtWidgets>

class TicTacToe : public QWidget
{
    Q_OBJECT

public:
    TicTacToe(QWidget *parent = nullptr) : QWidget(parent)
    {
        setWindowTitle("Tic-Tac-Toe");

        // Create the main grid layout
        QGridLayout *mainLayout = new QGridLayout(this);

        // Create the buttons for the Tic-Tac-Toe grid
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                buttons[row][col] = new QPushButton(this);
                buttons[row][col]->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                buttons[row][col]->setFont(QFont("Arial", 24));
                mainLayout->addWidget(buttons[row][col], row, col);
                connect(buttons[row][col], &QPushButton::clicked, this, [row, col, this]() { buttonClicked(row, col); });
            }
        }

        // Initialize game state
        resetGame();
    }

private slots:
    void buttonClicked(int row, int col)
    {
        if (buttons[row][col]->text().isEmpty() && !gameOver) {
            // Update the button text based on the current player
            buttons[row][col]->setText(currentPlayer == PlayerX ? "X" : "O");

            // Check for a winning condition
            if (checkWinCondition(row, col)) {
                gameOver = true;
                QString message = currentPlayer == PlayerX ? "Player X wins!" : "Player O wins!";
                QMessageBox::information(this, "Game Over", message);
            } else {
                // Switch to the next player
                currentPlayer = (currentPlayer == PlayerX) ? PlayerO : PlayerX;
            }
        }
    }

private:
    enum Player { PlayerX, PlayerO };

    QPushButton *buttons[3][3];
    Player currentPlayer;
    bool gameOver;

    void resetGame()
    {
        currentPlayer = PlayerX;
        gameOver = false;

        // Clear the button texts
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                buttons[row][col]->setText("");
            }
        }
    }

    bool checkWinCondition(int row, int col)
    {
        QString playerSymbol = (currentPlayer == PlayerX) ? "X" : "O";

        // Check horizontal line
        for (int c = 0; c < 3; ++c) {
            if (buttons[row][c]->text() != playerSymbol) {
                break;
            }
            if (c == 2) {
                return true;
            }
        }

        // Check vertical line
        for (int r = 0; r < 3; ++r) {
            if (buttons[r][col]->text() != playerSymbol) {
                break;
            }
            if (r == 2) {
                return true;
            }
        }

        // Check diagonal lines
        if (row == col) {
            for (int i = 0; i < 3; ++i) {
                if (buttons[i][i]->text() != playerSymbol) {
                    break;
                }
                if (i == 2) {
                    return true;
                }
            }
        }

        if (row + col == 2) {
            for (int i = 0; i < 3; ++i) {
                if (buttons[i][2 - i]->text() != playerSymbol) {
                    break;
                }
                if (i == 2) {
                    return true;
                }
            }
        }

        return false;
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    TicTacToe game;
    game.show();

    return app.exec();
}

#include "main.moc"
