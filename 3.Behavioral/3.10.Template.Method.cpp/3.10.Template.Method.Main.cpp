#include <iostream>
#include <memory>
/**
 * An abstract class that is common to several games in
 * which players play against the others, but only one is
 * playing at a given time.
 */

class GameObject
{
protected:
	int PlayersCount;

    virtual bool EndOfGame() = 0;

    virtual void InitializeGame() = 0;

    virtual void MakePlay(int player) = 0;

    virtual void PrintWinner() = 0;

public:
    /* A template method : */
	void PlayOneGame(int playersCount)
    {
        PlayersCount = playersCount;
        InitializeGame();

        int j = 0;

        while (!EndOfGame())
        {
            MakePlay(j);
            j = (j + 1) % playersCount;
        }

        PrintWinner();
    }
};

//Now we can extend this class in order to implement actual games:

class Monopoly : public GameObject
{
public:
	Monopoly()
	{
		;
	}

protected:
    /* Implementation of necessary concrete methods */
	void InitializeGame() override
    {
        // Initialize money
    }

    void MakePlay(int player) override
    {
        // Process one turn of player
    }

    bool EndOfGame() override
    {
        return true;
    }

    void PrintWinner() override
    {
        // Display who won
    }

    /* Specific declarations for the Monopoly game. */
    // ...
};

class Chess : public GameObject
{
public:
	Chess()
	{
		;
	}

protected:
	/* Implementation of necessary concrete methods */
	void InitializeGame() override
    {
        // Put the pieces on the board
    }

    void MakePlay(int player) override
    {
        // Process a turn for the player
    }

    bool EndOfGame() override
    {
        return true;
        // Return true if in Checkmate or Stalemate has been reached
    }

    void PrintWinner() override
    {
        // Display the winning player
    }

    /* Specific declarations for the chess game. */
    // ...
};

int main(int argc, char* argv[])
{
    std::shared_ptr<GameObject> game(new Monopoly());

    game->PlayOneGame(2);
}
