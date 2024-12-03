#include <iostream>
#include <cstdlib>

using namespace std;

enum enGameChoice { Stone = 1, Paper = 2, Scissors = 3 };

enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo {
	short RoundNumber = 0;
	enGameChoice Player1choice;
	enGameChoice ComputerChoice;
	enWinner Winner;
	string WinnerName;

};
struct stGameResult {
	short GameRound = 0;
	short Player1WinTimes = 0;
	short Computer1WinTime = 0;
	short DrawTimes = 0;
	enWinner GameWinner;
	string WinnerName = "";
};
int RandomNumber(int from, int to)
{
	int randNum = rand() % (to - from + 1) + from;
	return randNum;
}


string WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player1", "Computer", " No Winner" };
	return arrWinnerName[Winner - 1];
}


enWinner whoWinTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1choice == RoundInfo.ComputerChoice)
	{
		return enWinner::Draw;
	}
	switch (RoundInfo.Player1choice)
	{
	case enGameChoice::Stone:
		if (RoundInfo.ComputerChoice == enGameChoice::Paper)
		{
			return enWinner::Computer;
		}
	case enGameChoice::Paper:
		if (RoundInfo.ComputerChoice == enGameChoice::Scissors)
		{
			return enWinner::Computer;
		}
	case enGameChoice::Scissors:
		if (RoundInfo.ComputerChoice == enGameChoice::Stone)
		{
			return enWinner::Computer;
		}
		break;
	}
	return enWinner::Player;
}

string ChoiceName(enGameChoice Choice)
{
	string arrGameChoice[3] = { "Stone ", " Paper", " Scissors"};
	return arrGameChoice[Choice - 1];
}

void SetWinnerScreenColor(enWinner Winner)
{
	switch (Winner)
	{
	case enWinner::Player:
		system("color 2F"); //Green
		break;
	case enWinner::Computer:
		system("color 4F"); //Red
		break;
	case enWinner::Draw:
		system("color 6F"); //Yellow
		break;
	default:
		system("color 6F");
		break;
	}
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "\n______________Round [" << RoundInfo.RoundNumber << "] _________________\n\n";
	cout << "Player 1 Choice  : " << ChoiceName(RoundInfo.Player1choice) << endl;
	cout << "Computer Choice  : " << ChoiceName(RoundInfo.ComputerChoice) << endl;
	cout << "Round Winner     :    [" << RoundInfo.WinnerName << "] \n";
	cout << "________________________________________\n" << endl;
	SetWinnerScreenColor(RoundInfo.Winner);

}

enWinner WhoWonTheGame(short PlayerWinTime, short ComputerWinTimes)
{
	if (PlayerWinTime > ComputerWinTimes)
	{
		return enWinner::Player;
	}
	else if (ComputerWinTimes > PlayerWinTime)
	{
		return enWinner::Computer;
	}
	else
	{
		return enWinner::Draw;
	}
}

stGameResult FillGameResult(int GameRounds, short Player1WinTimes, short ComputerWinTimes, short DrawTimes)
{
	stGameResult GameResults;

	GameResults.GameRound = GameRounds;
	GameResults.Player1WinTimes = Player1WinTimes;
	GameResults.Computer1WinTime = ComputerWinTimes;
	GameResults.DrawTimes = DrawTimes;
	GameResults.GameWinner = WhoWonTheGame(Player1WinTimes, ComputerWinTimes);

	return GameResults;
}
enGameChoice ReadPlayerChoice()
{
	short Choice = 1;
	do
	{
		cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
		cin >> Choice;
	} while (Choice < 1 || Choice > 3);
	return (enGameChoice)Choice;
}

enGameChoice GetComputer()
{
	return (enGameChoice)RandomNumber(1, 3);
}

stGameResult PlayGame(short HowManyRounds)
{
	stRoundInfo RoundInfo;
	short player1WinTimes = 0, ComputerWinTimes = 0, DrawTimes = 0;
	for (short GameRound = 1; GameRound <= HowManyRounds; GameRound++)
	{
		cout << "\nRound [" << GameRound << "] begins:\n";
		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1choice = ReadPlayerChoice();
		RoundInfo.ComputerChoice = GetComputer();
		RoundInfo.Winner = whoWinTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

		if (RoundInfo.Winner == enWinner::Player)
		{
			player1WinTimes++;
		}
		else if (RoundInfo.Winner == enWinner::Computer)
		{
			ComputerWinTimes++;
		}
		else
		{
			DrawTimes++;
		}
		PrintRoundResults(RoundInfo);
	}
	return FillGameResult(HowManyRounds, player1WinTimes, ComputerWinTimes, DrawTimes);

}
string Tabs(short NumberOfTabs)
{
	string t = "";
	for (int i = 1; i < NumberOfTabs; i++)
	{
		t = t + "\t";
		cout << t;
	}
	return t;
}

void ShowGameOverScreen()
{
	cout << Tabs(2) << "______________________________________________________________\n";
	cout << Tabs(2) << "                                 +++  Game Over +++ \n";
	cout << Tabs(2) << "______________________________________________________________\n";
}

void ShowFinalGameResult(stGameResult GameResults)
{
	cout << endl;
	cout << Tabs(2) << "_____________________________[Game Results]_________________________\n\n";
	cout << Tabs(2) << "Game Rounds        : " << GameResults.GameRound << endl;
	cout << Tabs(2) << "Player1 Won Times  : " << GameResults.Player1WinTimes << endl;
	cout << Tabs(2) << "Computer Won Times : " << GameResults.Computer1WinTime << endl;
	cout << Tabs(2) << "Draw Times         : " << GameResults.DrawTimes << endl;
	cout << Tabs(2) << "Final Winner       : " << GameResults.WinnerName << endl;
	cout << Tabs(2) << "______________________________________________________________en\n";
}

short ReadHowManyRounds()
{
	short GameRounds = 1;
	do
	{
		cout << "How Many Rounds 1 To 10 ? \n";
		cin >> GameRounds;
	} while (GameRounds < 1 || GameRounds > 10);
	return GameRounds;
}
void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		stGameResult GameResults = PlayGame(ReadHowManyRounds());
		ShowGameOverScreen();
		ShowFinalGameResult(GameResults);
		cout << endl << Tabs(3) << "Do You Want To Play Again? Y/N ? ";
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	srand((unsigned)time(NULL));

	StartGame();
	
	return 0;
}