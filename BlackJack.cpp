#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <vector>
#include <Windows.h>
#include <string>
#include <fstream>

//color objects
void SetColor(int text, int bg)
{
	HANDLE cvet = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(cvet, (WORD)((bg << 4) | text));
}
//end

int main()
{
	//variables && list of random numbers
	setlocale(LC_ALL, "rus");
	system("color 2F");
	std::vector<int> numbers = { 2, 3, 4, 5, 6, 7, 8, 9, 10 }; //list of numbers cards
	std::vector<int> krup = { 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 }; //list of cards for krup
	srand(static_cast<unsigned int>(time(0)));
	int menu, start;
	bool flag1 = false, flag2 = false, flag3 = false, flag4 = false;
	int randomnum = rand() % numbers.size();
	int rk = rand() % krup.size();
	//end

	//file with score of game
	std::ofstream file;
	file.open("score.txt", std::ios_base::app);
	if (!file.is_open())
	{
		std::cerr << "Error! File is not open(";
		return 404;
	}
	//end
	
	//data and time
	auto currentTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm timeInfo;
	localtime_s(&timeInfo, &currentTime);
	char timeString[80];
	std::strftime(timeString, sizeof(timeString), "Date: %Y/%m/%d. Time: %H:%M:%S. ", &timeInfo);
	//end
	
	//number of game
	int lineNumber = 0;
	std::ifstream inputFile("score.txt");
	std::string line;
	while (std::getline(inputFile, line))
	{
		lineNumber++;
	}
	//end

	//menu
	std::cout << "Добро пожаловать в 'БлэкДжэк'! ;)                                                                Powered by Svetozarchik" << std::endl;
	std::cout << "Welcome to 'BlackJack'!" << std::endl;
	SetColor(4, 2);
	std::cout << "							     МЕНЮ" << std::endl;
	SetColor(15, 2);
	std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
	SetColor(4, 2);
	std::cout << "							НАЧАТЬ (Press 1)" << std::endl;
	std::cout << "						     ПРАВИЛА ИГРЫ (Press 2)" << std::endl;
	std::cout << "					   Replace the language with English (Press 3)" << std::endl;
	std::cout << "							ВЫХОД (Press 0)" << std::endl;
	std::cout << std::endl;
	std::cout << "Внимание! Игра сохраняет историю побед-поражений. Для того, чтобы её посмотреть, перейдите в файл 'score.txt'" << std::endl;
	SetColor(15, 2);
	std::cout << "------------------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cin >> menu;
	switch (menu)
	{
	case 1:
		flag1 = true;
		break;
	case 2:
		flag2 = true;
		break;
	case 3:
		flag4 = true;
		break;
	case 0:
		std::cout << "До встречи!" << std::endl;
		break;
	default:
		SetColor(4, 2);
		std::cerr << "ERROR 404" << std::endl;
		SetColor(15, 2);
		break;
	}
	//end

	//new language
	int lang;
	bool flag5 = false, flag6 = false;
	if (flag4 == true)
	{
		std::cout << "The language has been changed!" << std::endl;
		std::cout << "Do you want to read the rules or let's start the game?" << std::endl;
		SetColor(4, 2);
		std::cout << "Read (Press 1) | Skip (Press 0)" << std::endl;
		SetColor(15, 2);
		std::cin >> lang;
		switch (lang)
		{
		case 1:
			flag5 = true;
			break;
		case 0:
			flag6 = true;
			break;
		default:
			SetColor(4, 2);
			std::cout << "ERROR 404" << std::endl;
			SetColor(15, 2);
			break;
		}
	}
	//end

	//rules russian language
	if (flag2 == true)
	{
		SetColor(4, 2);
		std::cout << "Цель игры." << std::endl;
		SetColor(15, 2);
		std::cout << "-------------------------------------------------------------" << std::endl;
		std::cout << "Блэкджек, также известный как '21', имеет простую суть:" << std::endl;
		std::cout << "игроку нужно набрать 21 очко или ближайшее к этой цифре" << std::endl;
		std::cout << "значение в руке, превышающее сумму в руке у дилера," << std::endl;
		std::cout << "но ни в коем случае не превышающее 21. Если участник" << std::endl;
		std::cout << "превышает 21, он сгорает. В случае, если сумма очков одинакова" << std::endl;
		std::cout << "у него и дилера, партия заканчивается вничью и каждая сторона" << std::endl;
		std::cout << "остается при своем раскладе." << std::endl;
		std::cout << "-------------------------------------------------------------" << std::endl;
		SetColor(4, 2);
		std::cout << "НАЧАТЬ (Press 1), ВЫХОД (Press 0)" << std::endl;
		SetColor(15, 2);
		std::cin >> start;
		switch (start)
		{
		case 1:
			flag3 = true;
			break;
		case 0:
			std::cout << "До встречи!" << std::endl;
			break;
		default:
			SetColor(4, 2);
			std::cout << "ERROR 404" << std::endl;
			SetColor(15, 2);
			break;
		}
	}
	//end

	//rules english language
	if (flag5 == true)
	{
		SetColor(4, 2);
		std::cout << "The purpose of the game." << std::endl;
		SetColor(15, 2);
		std::cout << "-------------------------------------------------------------" << std::endl;
		std::cout << "Blackjack, also known as '21', has a simple essence:" << std::endl;
		std::cout << "the player needs to score 21 points or the closest to this figure" << std::endl;
		std::cout << "the value in the hand exceeding the amount in the dealer's hand," << std::endl;
		std::cout << "but in no case exceeding 21. If the participant" << std::endl;
		std::cout << "exceeds 21, it burns out. If the sum of the points is the same" << std::endl;
		std::cout << "for him and the dealer, the game ends in a draw and each side" << std::endl;
		std::cout << "it remains in its own scenario." << std::endl;
		std::cout << "-------------------------------------------------------------" << std::endl;
		SetColor(4, 2);
		std::cout << "START (Press 1), EXIT (Press 0)" << std::endl;
		SetColor(15, 2);
		std::cin >> start;
		switch (start)
		{
		case 1:
			flag6 = true;
			break;
		case 0:
			std::cout << "Goodbye!" << std::endl;
			break;
		default:
			SetColor(4, 2);
			std::cout << "ERROR 404" << std::endl;
			SetColor(15, 2);
			break;
		}
	}
	//end

	//start as russian language
	int random = rand() % numbers.size();
	bool score1 = false, score2 = false, score3 = false; //score1 is lose, score2 is draw and score3 is win
	int b, cnt = 0;
	cnt += numbers[randomnum];
	if (flag1 == true || flag3 == true)
	{
		// 1-st step
		std::cout << "Ваши очки: " << numbers[randomnum] << std::endl;
		std::cout << "Взять карту (Press 1) | Пас (Press 0)" << std::endl;
		std::cin >> b;
		//2-nd step
		if (b == 1 && cnt < 21)
		{
			cnt = numbers[random] + cnt;
			std::cout << "Ваши очки: " << cnt << std::endl;
			std::cout << "Взять карту (Press 1) | Пас (Press 0)" << std::endl;
			std::cin >> b;
			int randomn = rand() % numbers.size();
			//3-d step
			if (b == 1 && cnt < 21)
			{
				cnt = numbers[randomn] + cnt;
				std::cout << "Ваши очки: " << cnt << std::endl;
				std::cout << "Взять карту (Press 1) | Пас (Press 0)" << std::endl;
				std::cin >> b;
				int rando = rand() % numbers.size();
				//4-th step
				if (b == 1 && cnt < 21)
				{
					cnt = numbers[rando] + cnt;
					std::cout << "Ваши очки: " << cnt << std::endl;
					std::cout << "Взять карту (Press 1) | Пас (Press 0)" << std::endl;
					std::cin >> b;
					//5-th step
					int ran = rand() % numbers.size();
					if (b == 1 && cnt < 21)
					{
						cnt = numbers[ran] + cnt;
						std::cout << "Ваши очки: " << cnt << std::endl;
						std::cout << "Взять карту (Press 1) | Пас (Press 0)" << std::endl;
						std::cin >> b;
						//6-th step
						int ra = rand() % numbers.size();
						if (b == 1 && cnt < 21)
						{
							cnt = numbers[ra] + cnt;
							std::cout << "Ваши очки: " << cnt << std::endl;
							std::cout << "Взять карту (Press 1) | Пас (Press 0)" << std::endl;
							std::cin >> b;
							//7-n step
							int r = rand() % numbers.size();
							if (b == 1 && cnt < 21)
							{
								cnt = numbers[r] + cnt;
								std::cout << "Ваши очки: " << cnt << std::endl;
								std::cout << "Взять карту (Press 1) | Пас (Press 0)" << std::endl;
								std::cin >> b;
							}
							else if (b == 1 && cnt > 21 && krup[rk] == 21)
							{
								std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
								std::cout << "Очки крупье: " << krup[rk] << std::endl;
								score1 = true;
							}
							else if (b == 1 && cnt > 21 && krup[rk] < 21)
							{
								std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
								std::cout << "Очки крупье: " << krup[rk] << std::endl;
								score1 = true;
							}
							else if (b == 1 && cnt > 21 && krup[rk] > 21)
							{
								std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
								std::cout << "Очки крупье: " << krup[rk] << std::endl;
								score2 = true;
							}
							else if (b == 0 && cnt == 21 && krup[rk] != 21)
							{
								std::cout << "Ваши очки: " << cnt << " Вы победили!!!" << std::endl;
								std::cout << "Очки крупье: " << krup[rk] << std::endl;
								score3 = true;
							}
							else if (b == 0 && cnt == 21 && krup[rk] == 21)
							{
								std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
								std::cout << "Очки крупье: " << krup[rk] << std::endl;
								score2 = true;
							}
							else if (b == 0 && cnt > krup[rk] && cnt > 21 && krup[rk] > 21)
							{
								std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
								std::cout << "Очки крупье: " << krup[rk] << std::endl;
								score2 = true;
							}
							else if (b == 0 && cnt < krup[rk] && cnt > 21 && krup[rk] > 21)
							{
								std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
								std::cout << "Очки крупье: " << krup[rk] << std::endl;
								score2 = true;
							}
							else if (b == 0 && cnt < krup[rk] && cnt < 21 && krup[rk] < 21)
							{
								std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
								std::cout << "Очки крупье: " << krup[rk] << std::endl;
								score1 = true;
							}
							else if (b == 0 && cnt > krup[rk] && cnt < 21 && krup[rk] < 21)
							{
								std::cout << "Ваши очки: " << cnt << " Вы победили!!!" << std::endl;
								std::cout << "Очки крупье: " << krup[rk] << std::endl;
								score3 = true;
							}
							else if (b == 0 && cnt > krup[rk] && cnt < 21 && krup[rk] > 21)
							{
								std::cout << "Ваши очки: " << cnt << " Вы победили!!!" << std::endl;
								std::cout << "Очки крупье: " << krup[rk] << std::endl;
								score3 = true;
							}
							else if (b == 0 && cnt > 21 && krup[rk] > cnt)
							{
								std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
								std::cout << "Очки крупье: " << krup[rk] << std::endl;
								score2 = true;
							}
							else if (b == 0 && cnt > 21 && krup[rk] < cnt)
							{
								std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
								std::cout << "Очки крупье: " << krup[rk] << std::endl;
								score1 = true;
							}
							else if (b == 0 && cnt < krup[rk] && cnt < 21 && krup[rk] > 21)
							{
								std::cout << "Ваши очки: " << cnt << " Вы победили!!!" << std::endl;
								std::cout << "Очки крупье: " << krup[rk] << std::endl;
								score3 = true;
							}
							else if (b == 0 && cnt != 21 && krup[rk] == 21)
							{
								std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
								std::cout << "Очки крупье: " << krup[rk] << std::endl;
								score1 = true;
							}
							//end 7-n
						}
						else if (b == 1 && cnt > 21 && krup[rk] == 21)
						{
							std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
							std::cout << "Очки крупье: " << krup[rk] << std::endl;
							score1 = true;
						}
						else if (b == 1 && cnt > 21 && krup[rk] < 21)
						{
							std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
							std::cout << "Очки крупье: " << krup[rk] << std::endl;
							score1 = true;
						}
						else if (b == 1 && cnt > 21 && krup[rk] > 21)
						{
							std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
							std::cout << "Очки крупье: " << krup[rk] << std::endl;
							score2 = true;
						}
						else if (b == 0 && cnt == 21 && krup[rk] == 21)
						{
							std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
							std::cout << "Очки крупье: " << krup[rk] << std::endl;
							score2 = true;
						}
						else if (b == 0 && cnt == 21 && krup[rk] != 21)
						{
							std::cout << "Ваши очки: " << cnt << " Вы победили!!!" << std::endl;
							std::cout << "Очки крупье: " << krup[rk] << std::endl;
							score3 = true;
						}
						else if (b == 0 && cnt > krup[rk] && cnt < 21 && krup[rk] > 21)
						{
							std::cout << "Ваши очки: " << cnt << " Вы победили!!!" << std::endl;
							std::cout << "Очки крупье: " << krup[rk] << std::endl;
							score3 = true;
						}
						else if (b == 0 && cnt > krup[rk] && cnt > 21 && krup[rk] > 21)
						{
							std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
							std::cout << "Очки крупье: " << krup[rk] << std::endl;
							score2 = true;
						}
						else if (b == 0 && cnt < krup[rk] && cnt > 21 && krup[rk] > 21)
						{
							std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
							std::cout << "Очки крупье: " << krup[rk] << std::endl;
							score2 = true;
						}
						else if (b == 0 && cnt < krup[rk] && cnt < 21 && krup[rk] < 21)
						{
							std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
							std::cout << "Очки крупье: " << krup[rk] << std::endl;
							score1 = true;
						}
						else if (b == 0 && cnt > krup[rk] && cnt < 21 && krup[rk] < 21)
						{
							std::cout << "Ваши очки: " << cnt << " Вы победили!!!" << std::endl;
							std::cout << "Очки крупье: " << krup[rk] << std::endl;
							score3 = true;
						}
						else if (b == 0 && cnt > 21 && krup[rk] > cnt)
						{
							std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
							std::cout << "Очки крупье: " << krup[rk] << std::endl;
							score2 = true;
						}
						else if (b == 0 && cnt > 21 && krup[rk] < cnt)
						{
							std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
							std::cout << "Очки крупье: " << krup[rk] << std::endl;
							score1 = true;
						}
						else if (b == 0 && cnt < krup[rk] && cnt < 21 && krup[rk] > 21)
						{
							std::cout << "Ваши очки: " << cnt << " Вы победили!!!" << std::endl;
							std::cout << "Очки крупье: " << krup[rk] << std::endl;
							score3 = true;
						}
						else if (b == 0 && cnt != 21 && krup[rk] == 21)
						{
							std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
							std::cout << "Очки крупье: " << krup[rk] << std::endl;
							score1 = true;
						}
						//end 6-th
					}
					else if (b == 1 && cnt > 21 && krup[rk] == 21)
					{
						std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
						std::cout << "Очки крупье: " << krup[rk] << std::endl;
						score1 = true;
					}
					else if (b == 1 && cnt > 21 && krup[rk] < 21)
					{
						std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
						std::cout << "Очки крупье: " << krup[rk] << std::endl;
						score1 = true;
					}
					else if (b == 1 && cnt > 21 && krup[rk] > 21)
					{
						std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
						std::cout << "Очки крупье: " << krup[rk] << std::endl;
						score2 = true;
					}
					else if (b == 0 && cnt > krup[rk] && cnt < 21 && krup[rk] > 21)
					{
						std::cout << "Ваши очки: " << cnt << " Вы победили!!!" << std::endl;
						std::cout << "Очки крупье: " << krup[rk] << std::endl;
						score3 = true;
					}
					else if (b == 0 && cnt == 21 && krup[rk] != 21)
					{
						std::cout << "Ваши очки: " << cnt << " Вы победили!!!" << std::endl;
						std::cout << "Очки крупье: " << krup[rk] << std::endl;
						score3 = true;
					}
					else if (b == 0 && cnt == 21 && krup[rk] == 21)
					{
						std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
						std::cout << "Очки крупье: " << krup[rk] << std::endl;
						score2 = true;
					}
					else if (b == 0 && cnt > krup[rk] && cnt > 21 && krup[rk] > 21)
					{
						std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
						std::cout << "Очки крупье: " << krup[rk] << std::endl;
						score2 = true;
					}
					else if (b == 0 && cnt < krup[rk] && cnt > 21 && krup[rk] > 21)
					{
						std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
						std::cout << "Очки крупье: " << krup[rk] << std::endl;
						score2 = true;
					}
					else if (b == 0 && cnt < krup[rk] && cnt < 21 && krup[rk] < 21)
					{
						std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
						std::cout << "Очки крупье: " << krup[rk] << std::endl;
						score1 = true;
					}
					else if (b == 0 && cnt > krup[rk] && cnt < 21 && krup[rk] < 21)
					{
						std::cout << "Ваши очки: " << cnt << " Вы победили!!!" << std::endl;
						std::cout << "Очки крупье: " << krup[rk] << std::endl;
						score3 = true;
					}
					else if (b == 0 && cnt > 21 && krup[rk] > cnt)
					{
						std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
						std::cout << "Очки крупье: " << krup[rk] << std::endl;
						score2 = true;
					}
					else if (b == 0 && cnt > 21 && krup[rk] < cnt)
					{
						std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
						std::cout << "Очки крупье: " << krup[rk] << std::endl;
						score1 = true;
					}
					else if (b == 0 && cnt < krup[rk] && cnt < 21 && krup[rk] > 21)
					{
						std::cout << "Ваши очки: " << cnt << " Вы победили!!!" << std::endl;
						std::cout << "Очки крупье: " << krup[rk] << std::endl;
						score3 = true;
					}
					else if (b == 0 && cnt != 21 && krup[rk] == 21)
					{
						std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
						std::cout << "Очки крупье: " << krup[rk] << std::endl;
						score1 = true;
					}
					//end 5-th
				}
				else if (b == 1 && cnt > 21 && krup[rk] == 21)
				{
					std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
					std::cout << "Очки крупье: " << krup[rk] << std::endl;
					score1 = true;
				}
				else if (b == 1 && cnt > 21 && krup[rk] < 21)
				{
					std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
					std::cout << "Очки крупье: " << krup[rk] << std::endl;
					score1 = true;
				}
				else if (b == 1 && cnt > 21 && krup[rk] > 21)
				{
					std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
					std::cout << "Очки крупье: " << krup[rk] << std::endl;
					score2 = true;
				}
				else if (b == 0 && cnt > krup[rk] && cnt < 21 && krup[rk] > 21)
				{
					std::cout << "Ваши очки: " << cnt << " Вы победили!!!" << std::endl;
					std::cout << "Очки крупье: " << krup[rk] << std::endl;
					score3 = true;
				}
				else if (b == 0 && cnt == 21 && krup[rk] != 21)
				{
					std::cout << "Ваши очки: " << cnt << " Вы победили!!!" << std::endl;
					std::cout << "Очки крупье: " << krup[rk] << std::endl;
					score3 = true;
				}
				else if (b == 0 && cnt == 21 && krup[rk] == 21)
				{
					std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
					std::cout << "Очки крупье: " << krup[rk] << std::endl;
					score2 = true;
				}
				else if (b == 0 && cnt > krup[rk] && cnt > 21 && krup[rk] > 21)
				{
					std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
					std::cout << "Очки крупье: " << krup[rk] << std::endl;
					score2 = true;
				}
				else if (b == 0 && cnt < krup[rk] && cnt > 21 && krup[rk] > 21)
				{
					std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
					std::cout << "Очки крупье: " << krup[rk] << std::endl;
					score2 = true;
				}
				else if (b == 0 && cnt < krup[rk] && cnt < 21 && krup[rk] < 21)
				{
					std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
					std::cout << "Очки крупье: " << krup[rk] << std::endl;
					score1 = true;
				}
				else if (b == 0 && cnt > krup[rk] && cnt < 21 && krup[rk] < 21)
				{
					std::cout << "Ваши очки: " << cnt << " Вы победили!!!" << std::endl;
					std::cout << "Очки крупье: " << krup[rk] << std::endl;
					score3 = true;
				}
				else if (b == 0 && cnt > 21 && krup[rk] > cnt)
				{
					std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
					std::cout << "Очки крупье: " << krup[rk] << std::endl;
					score2 = true;
				}
				else if (b == 0 && cnt > 21 && krup[rk] < cnt)
				{
					std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
					std::cout << "Очки крупье: " << krup[rk] << std::endl;
					score1 = true;
				}
				else if (b == 0 && cnt < krup[rk] && cnt < 21 && krup[rk] > 21)
				{
					std::cout << "Ваши очки: " << cnt << " Вы победили!!!" << std::endl;
					std::cout << "Очки крупье: " << krup[rk] << std::endl;
					score3 = true;
				}
				else if (b == 0 && cnt != 21 && krup[rk] == 21)
				{
					std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
					std::cout << "Очки крупье: " << krup[rk] << std::endl;
					score1 = true;
				}
				//end 4-th
			}
			else if (b == 1 && cnt > 21 && krup[rk] == 21)
			{
				std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
				std::cout << "Очки крупье: " << krup[rk] << std::endl;
				score1 = true;
			}
			else if (b == 0 && cnt > krup[rk] && cnt < 21 && krup[rk] > 21)
			{
				std::cout << "Ваши очки: " << cnt << " Вы победили!!!" << std::endl;
				std::cout << "Очки крупье: " << krup[rk] << std::endl;
				score3 = true;
			}
			else if (b == 1 && cnt > 21 && krup[rk] < 21)
			{
				std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
				std::cout << "Очки крупье: " << krup[rk] << std::endl;
				score1 = true;
			}
			else if (b == 1 && cnt > 21 && krup[rk] > 21)
			{
				std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
				std::cout << "Очки крупье: " << krup[rk] << std::endl;
				score2 = true;
			}
			else if (b == 0 && cnt > krup[rk] && cnt > 21 && krup[rk] > 21)
			{
				std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
				std::cout << "Очки крупье: " << krup[rk] << std::endl;
				score2 = true;
			}
			else if (b == 0 && cnt < krup[rk] && cnt > 21 && krup[rk] > 21)
			{
				std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
				std::cout << "Очки крупье: " << krup[rk] << std::endl;
				score2 = true;
			}
			else if (b == 0 && cnt == 21 && krup[rk] != 21)
			{
				std::cout << "Ваши очки: " << cnt << " Вы победили!!!" << std::endl;
				std::cout << "Очки крупье: " << krup[rk] << std::endl;
				score3 = true;
			}
			else if (b == 0 && cnt != 21 && krup[rk] == 21)
			{
				std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
				std::cout << "Очки крупье: " << krup[rk] << std::endl;
			}
			else if (b == 0 && cnt == 21 && krup[rk] == 21)
			{
				std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
				std::cout << "Очки крупье: " << krup[rk] << std::endl;
				score2 = true;
			}
			else if (b == 0 && cnt < krup[rk] && cnt < 21 && krup[rk] < 21)
			{
				std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
				std::cout << "Очки крупье: " << krup[rk] << std::endl;
				score1 = true;
			}
			else if (b == 0 && cnt > krup[rk] && cnt < 21 && krup[rk] < 21)
			{
				std::cout << "Ваши очки: " << cnt << " Вы победили!!!" << std::endl;
				std::cout << "Очки крупье: " << krup[rk] << std::endl;
				score3 = true;
			}
			else if (b == 0 && cnt > 21 && krup[rk] > cnt)
			{
				std::cout << "Ваши очки: " << cnt << " Ничья!" << std::endl;
				std::cout << "Очки крупье: " << krup[rk] << std::endl;
				score2 = true;
			}
			else if (b == 0 && cnt > 21 && krup[rk] < cnt)
			{
				std::cout << "Ваши очки: " << cnt << " Вы проиграли!" << std::endl;
				std::cout << "Очки крупье: " << krup[rk] << std::endl;
				score1 = true;
			}
			else if (b == 0 && cnt < krup[rk] && cnt < 21 && krup[rk] > 21)
			{
				std::cout << "Ваши очки: " << cnt << " Вы победили!!!" << std::endl;
				std::cout << "Очки крупье: " << krup[rk] << std::endl;
				score3 = true;
			}

			//end 3-d
		}
		else
		{
			std::cout << "Ваши очки: " << numbers[randomnum] << " Вы проиграли!" << std::endl;
			std::cout << "Очки крупье: " << krup[rk] << std::endl;
			score1 = true;
		}
		//end 2-nd
	}
	//end 1-st

	//start english language
	if (flag6 == true)
	{
		// 1-st step
		std::cout << "Your score: " << numbers[randomnum] << std::endl;
		std::cout << "Pick the card (Press 1) | Miss (Press 0)" << std::endl;
		std::cin >> b;
		//2-nd step
		if (b == 1 && cnt < 21)
		{
			cnt = numbers[random] + cnt;
			std::cout << "Your score: " << cnt << std::endl;
			std::cout << "Pick the card (Press 1) | Miss (Press 0)" << std::endl;
			std::cin >> b;
			int randomn = rand() % numbers.size();
			//3-d step
			if (b == 1 && cnt < 21)
			{
				cnt = numbers[randomn] + cnt;
				std::cout << "Your score: " << cnt << std::endl;
				std::cout << "Pick the card (Press 1) | Miss (Press 0)" << std::endl;
				std::cin >> b;
				int rando = rand() % numbers.size();
				//4-th step
				if (b == 1 && cnt < 21)
				{
					cnt = numbers[rando] + cnt;
					std::cout << "Your score: " << cnt << std::endl;
					std::cout << "Pick the card (Press 1) | Miss (Press 0)" << std::endl;
					std::cin >> b;
					//5-th step
					int ran = rand() % numbers.size();
					if (b == 1 && cnt < 21)
					{
						cnt = numbers[ran] + cnt;
						std::cout << "Your score: " << cnt << std::endl;
						std::cout << "Pick the card (Press 1) | Miss (Press 0)" << std::endl;
						std::cin >> b;
						//6-th step
						int ra = rand() % numbers.size();
						if (b == 1 && cnt < 21)
						{
							cnt = numbers[ra] + cnt;
							std::cout << "Your score: " << cnt << std::endl;
							std::cout << "Pick the card (Press 1) | Miss (Press 0)" << std::endl;
							std::cin >> b;
							//7-n step
							int r = rand() % numbers.size();
							if (b == 1 && cnt < 21)
							{
								cnt = numbers[r] + cnt;
								std::cout << "Your score: " << cnt << std::endl;
								std::cout << "Pick the card (Press 1) | Miss (Press 0)" << std::endl;
								std::cin >> b;
							}
							else if (b == 1 && cnt > 21 && krup[rk] == 21)
							{
								std::cout << "Your score: " << cnt << " You lose!" << std::endl;
								std::cout << "Dealer score: " << krup[rk] << std::endl;
								score1 = true;
							}
							else if (b == 0 && cnt > krup[rk] && cnt < 21 && krup[rk] > 21)
							{
								std::cout << "Your score: " << cnt << " You win!!!" << std::endl;
								std::cout << "Dealer score: " << krup[rk] << std::endl;
								score3 = true;
							}
							else if (b == 1 && cnt > 21 && krup[rk] < 21)
							{
								std::cout << "Your score: " << cnt << " You lose!" << std::endl;
								std::cout << "Dealer score: " << krup[rk] << std::endl;
								score1 = true;
							}
							else if (b == 1 && cnt > 21 && krup[rk] > 21)
							{
								std::cout << "Your score: " << cnt << " Draw!" << std::endl;
								std::cout << "Dealer score: " << krup[rk] << std::endl;
								score2 = true;
							}
							else if (b == 0 && cnt == 21 && krup[rk] != 21)
							{
								std::cout << "Your score: " << cnt << " You win!!!" << std::endl;
								std::cout << "Dealer score: " << krup[rk] << std::endl;
								score3 = true;
							}
							else if (b == 0 && cnt == 21 && krup[rk] == 21)
							{
								std::cout << "Your score: " << cnt << " Draw!" << std::endl;
								std::cout << "Dealer score: " << krup[rk] << std::endl;
								score2 = true;
							}
							else if (b == 0 && cnt > krup[rk] && cnt > 21 && krup[rk] > 21)
							{
								std::cout << "Your score: " << cnt << " Draw!" << std::endl;
								std::cout << "Dealer score: " << krup[rk] << std::endl;
								score2 = true;
							}
							else if (b == 0 && cnt < krup[rk] && cnt > 21 && krup[rk] > 21)
							{
								std::cout << "Your score: " << cnt << " Draw!" << std::endl;
								std::cout << "Dealer score: " << krup[rk] << std::endl;
								score2 = true;
							}
							else if (b == 0 && cnt < krup[rk] && cnt < 21 && krup[rk] < 21)
							{
								std::cout << "Your score: " << cnt << " You lose!" << std::endl;
								std::cout << "Dealer score: " << krup[rk] << std::endl;
								score1 = true;
							}
							else if (b == 0 && cnt > krup[rk] && cnt < 21 && krup[rk] < 21)
							{
								std::cout << "Your score: " << cnt << " You win!!!" << std::endl;
								std::cout << "Dealer score: " << krup[rk] << std::endl;
								score3 = true;
							}
							else if (b == 0 && cnt > 21 && krup[rk] > cnt)
							{
								std::cout << "Your score: " << cnt << " Draw!" << std::endl;
								std::cout << "Dealer score: " << krup[rk] << std::endl;
							}
							else if (b == 0 && cnt > 21 && krup[rk] < cnt)
							{
								std::cout << "Your score: " << cnt << " You lose!" << std::endl;
								std::cout << "Dealer score: " << krup[rk] << std::endl;
								score1 = true;
							}
							else if (b == 0 && cnt < krup[rk] && cnt < 21 && krup[rk] > 21)
							{
								std::cout << "Your score: " << cnt << " You win!!!" << std::endl;
								std::cout << "Dealer score: " << krup[rk] << std::endl;
								score3 = true;
							}
							else if (b == 0 && cnt != 21 && krup[rk] == 21)
							{
								std::cout << "Your score: " << cnt << " You lose!" << std::endl;
								std::cout << "Dealer score: " << krup[rk] << std::endl;
								score1 = true;
							}
							//end 7-n
						}
						else if (b == 1 && cnt > 21 && krup[rk] == 21)
						{
							std::cout << "Your score: " << cnt << " You lose!" << std::endl;
							std::cout << "Dealer score: " << krup[rk] << std::endl;
							score1 = true;
						}
						else if (b == 0 && cnt > krup[rk] && cnt < 21 && krup[rk] > 21)
						{
							std::cout << "Your score: " << cnt << " You win!!!" << std::endl;
							std::cout << "Dealer score: " << krup[rk] << std::endl;
							score3 = true;
						}
						else if (b == 1 && cnt > 21 && krup[rk] < 21)
						{
							std::cout << "Your score: " << cnt << " You lose" << std::endl;
							std::cout << "Dealer score: " << krup[rk] << std::endl;
							score1 = true;
						}
						else if (b == 1 && cnt > 21 && krup[rk] > 21)
						{
							std::cout << "Your score: " << cnt << " Draw" << std::endl;
							std::cout << "Dealer score: " << krup[rk] << std::endl;
							score2 = true;
						}
						else if (b == 0 && cnt == 21 && krup[rk] == 21)
						{
							std::cout << "Your score: " << cnt << " Draw!" << std::endl;
							std::cout << "Dealer score: " << krup[rk] << std::endl;
							score2 = true;
						}
						else if (b == 0 && cnt == 21 && krup[rk] != 21)
						{
							std::cout << "Your score: " << cnt << " You win!!!" << std::endl;
							std::cout << "Dealer score: " << krup[rk] << std::endl;
							score3 = true;
						}
						else if (b == 0 && cnt > krup[rk] && cnt > 21 && krup[rk] > 21)
						{
							std::cout << "Your score: " << cnt << " Draw" << std::endl;
							std::cout << "Dealer score: " << krup[rk] << std::endl;
							score2 = true;
						}
						else if (b == 0 && cnt < krup[rk] && cnt > 21 && krup[rk] > 21)
						{
							std::cout << "Your score: " << cnt << " Draw" << std::endl;
							std::cout << "Dealer score: " << krup[rk] << std::endl;
							score2 = true;
						}
						else if (b == 0 && cnt < krup[rk] && cnt < 21 && krup[rk] < 21)
						{
							std::cout << "Your score: " << cnt << " You lose" << std::endl;
							std::cout << "Dealer score: " << krup[rk] << std::endl;
							score1 = true;
						}
						else if (b == 0 && cnt > krup[rk] && cnt < 21 && krup[rk] < 21)
						{
							std::cout << "Your score: " << cnt << " You win!!!" << std::endl;
							std::cout << "Dealer score: " << krup[rk] << std::endl;
							score3 = true;
						}
						else if (b == 0 && cnt > 21 && krup[rk] > cnt)
						{
							std::cout << "Your score: " << cnt << " Draw" << std::endl;
							std::cout << "Dealer score: " << krup[rk] << std::endl;
							score2 = true;
						}
						else if (b == 0 && cnt > 21 && krup[rk] < cnt)
						{
							std::cout << "Your score: " << cnt << " You lose" << std::endl;
							std::cout << "Dealer score: " << krup[rk] << std::endl;
							score1 = true;
						}
						else if (b == 0 && cnt < krup[rk] && cnt < 21 && krup[rk] > 21)
						{
							std::cout << "Your score: " << cnt << " You win!!!" << std::endl;
							std::cout << "Dealer score: " << krup[rk] << std::endl;
							score3 = true;
						}
						else if (b == 0 && cnt != 21 && krup[rk] == 21)
						{
							std::cout << "Your score: " << cnt << " You lose" << std::endl;
							std::cout << "Dealer score: " << krup[rk] << std::endl;
							score1 = true;
						}
						//end 6-th
					}
					else if (b == 1 && cnt > 21 && krup[rk] == 21)
					{
						std::cout << "Your score: " << cnt << " You lose" << std::endl;
						std::cout << "Dealer score: " << krup[rk] << std::endl;
						score1 = true;
					}
					else if (b == 0 && cnt > krup[rk] && cnt < 21 && krup[rk] > 21)
					{
						std::cout << "Your score: " << cnt << " You win!!!" << std::endl;
						std::cout << "Dealer score: " << krup[rk] << std::endl;
						score3 = true;
					}
					else if (b == 1 && cnt > 21 && krup[rk] < 21)
					{
						std::cout << "Your score: " << cnt << " You lose" << std::endl;
						std::cout << "Dealer score: " << krup[rk] << std::endl;
						score1 = true;
					}
					else if (b == 1 && cnt > 21 && krup[rk] > 21)
					{
						std::cout << "Your score: " << cnt << " Draw" << std::endl;
						std::cout << "Dealer score: " << krup[rk] << std::endl;
						score2 = true;
					}
					else if (b == 0 && cnt == 21 && krup[rk] != 21)
					{
						std::cout << "Your score: " << cnt << " You win!!!" << std::endl;
						std::cout << "Dealer score: " << krup[rk] << std::endl;
						score3 = true;
					}
					else if (b == 0 && cnt == 21 && krup[rk] == 21)
					{
						std::cout << "Your score: " << cnt << " Draw!" << std::endl;
						std::cout << "Dealer score: " << krup[rk] << std::endl;
						score2 = true;
					}
					else if (b == 0 && cnt > krup[rk] && cnt > 21 && krup[rk] > 21)
					{
						std::cout << "Your score: " << cnt << " Draw" << std::endl;
						std::cout << "Dealer score: " << krup[rk] << std::endl;
						score2 = true;
					}
					else if (b == 0 && cnt < krup[rk] && cnt > 21 && krup[rk] > 21)
					{
						std::cout << "Your score: " << cnt << " Draw" << std::endl;
						std::cout << "Dealer score: " << krup[rk] << std::endl;
						score2 = true;
					}
					else if (b == 0 && cnt < krup[rk] && cnt < 21 && krup[rk] < 21)
					{
						std::cout << "Your score: " << cnt << " You lose" << std::endl;
						std::cout << "Dealer score: " << krup[rk] << std::endl;
						score1 = true;
					}
					else if (b == 0 && cnt > krup[rk] && cnt < 21 && krup[rk] < 21)
					{
						std::cout << "Your score: " << cnt << " You win!!!" << std::endl;
						std::cout << "Dealer score: " << krup[rk] << std::endl;
						score3 = true;
					}
					else if (b == 0 && cnt > 21 && krup[rk] > cnt)
					{
						std::cout << "Your score: " << cnt << " Draw" << std::endl;
						std::cout << "Dealer score: " << krup[rk] << std::endl;
						score2 = true;
					}
					else if (b == 0 && cnt > 21 && krup[rk] < cnt)
					{
						std::cout << "Your score: " << cnt << " You lose" << std::endl;
						std::cout << "Dealer score: " << krup[rk] << std::endl;
						score1 = true;
					}
					else if (b == 0 && cnt < krup[rk] && cnt < 21 && krup[rk] > 21)
					{
						std::cout << "Your score: " << cnt << " You win!!!" << std::endl;
						std::cout << "Dealer score: " << krup[rk] << std::endl;
						score3 = true;
					}
					else if (b == 0 && cnt != 21 && krup[rk] == 21)
					{
						std::cout << "Your score: " << cnt << " You lose" << std::endl;
						std::cout << "Dealer score: " << krup[rk] << std::endl;
						score1 = true;
					}
					//end 5-th
				}
				else if (b == 1 && cnt > 21 && krup[rk] == 21)
				{
					std::cout << "Your score: " << cnt << " You lose" << std::endl;
					std::cout << "Dealer score: " << krup[rk] << std::endl;
					score1 = true;
				}
				else if (b == 0 && cnt > krup[rk] && cnt < 21 && krup[rk] > 21)
				{
					std::cout << "Your score: " << cnt << " You win!!!" << std::endl;
					std::cout << "Dealer score: " << krup[rk] << std::endl;
					score3 = true;
				}
				else if (b == 1 && cnt > 21 && krup[rk] < 21)
				{
					std::cout << "Your score: " << cnt << " You lose" << std::endl;
					std::cout << "Dealer score: " << krup[rk] << std::endl;
					score1 = true;
				}
				else if (b == 1 && cnt > 21 && krup[rk] > 21)
				{
					std::cout << "Your score: " << cnt << " Draw" << std::endl;
					std::cout << "Dealer score: " << krup[rk] << std::endl;
					score2 = true;
				}
				else if (b == 0 && cnt == 21 && krup[rk] != 21)
				{
					std::cout << "Your score: " << cnt << " You win!!!" << std::endl;
					std::cout << "Dealer score: " << krup[rk] << std::endl;
					score3 = true;
				}
				else if (b == 0 && cnt == 21 && krup[rk] == 21)
				{
					std::cout << "Your score: " << cnt << " Draw!" << std::endl;
					std::cout << "Dealer score: " << krup[rk] << std::endl;
					score2 = true;
				}
				else if (b == 0 && cnt > krup[rk] && cnt > 21 && krup[rk] > 21)
				{
					std::cout << "Your score: " << cnt << " Draw" << std::endl;
					std::cout << "Dealer score: " << krup[rk] << std::endl;
					score2 = true;
				}
				else if (b == 0 && cnt < krup[rk] && cnt > 21 && krup[rk] > 21)
				{
					std::cout << "Your score: " << cnt << " Draw" << std::endl;
					std::cout << "Dealer score: " << krup[rk] << std::endl;
					score2 = true;
				}
				else if (b == 0 && cnt < krup[rk] && cnt < 21 && krup[rk] < 21)
				{
					std::cout << "Your score: " << cnt << " You lose" << std::endl;
					std::cout << "Dealer score: " << krup[rk] << std::endl;
					score1 = true;
				}
				else if (b == 0 && cnt > krup[rk] && cnt < 21 && krup[rk] < 21)
				{
					std::cout << "Your score: " << cnt << " You win!!!" << std::endl;
					std::cout << "Dealer score: " << krup[rk] << std::endl;
					score3 = true;
				}
				else if (b == 0 && cnt > 21 && krup[rk] > cnt)
				{
					std::cout << "Your score: " << cnt << " Draw" << std::endl;
					std::cout << "Dealer score: " << krup[rk] << std::endl;
					score2 = true;
				}
				else if (b == 0 && cnt > 21 && krup[rk] < cnt)
				{
					std::cout << "Your score: " << cnt << " You lose" << std::endl;
					std::cout << "Dealer score: " << krup[rk] << std::endl;
					score1 = true;
				}
				else if (b == 0 && cnt < krup[rk] && cnt < 21 && krup[rk] > 21)
				{
					std::cout << "Your score: " << cnt << " You win!!!" << std::endl;
					std::cout << "Dealer score: " << krup[rk] << std::endl;
					score3 = true;
				}
				else if (b == 0 && cnt != 21 && krup[rk] == 21)
				{
					std::cout << "Your score: " << cnt << " You lose" << std::endl;
					std::cout << "Dealer score: " << krup[rk] << std::endl;
					score1 = true;
				}
				//end 4-th
			}
			else if (b == 1 && cnt > 21 && krup[rk] == 21)
			{
				std::cout << "Your score: " << cnt << " You lose" << std::endl;
				std::cout << "Dealer score: " << krup[rk] << std::endl;
				score1 = true;
			}
			else if (b == 0 && cnt > krup[rk] && cnt < 21 && krup[rk] > 21)
			{
				std::cout << "Your score: " << cnt << " You win!!!" << std::endl;
				std::cout << "Dealer score: " << krup[rk] << std::endl;
				score3 = true;
			}
			else if (b == 1 && cnt > 21 && krup[rk] < 21)
			{
				std::cout << "Your score: " << cnt << " You lose" << std::endl;
				std::cout << "Dealer score: " << krup[rk] << std::endl;
				score1 = true;
			}
			else if (b == 1 && cnt > 21 && krup[rk] > 21)
			{
				std::cout << "Your score: " << cnt << " Draw" << std::endl;
				std::cout << "Dealer score: " << krup[rk] << std::endl;
				score2 = true;
			}
			else if (b == 0 && cnt > krup[rk] && cnt > 21 && krup[rk] > 21)
			{
				std::cout << "Your score: " << cnt << " Draw" << std::endl;
				std::cout << "Dealer score: " << krup[rk] << std::endl;
				score2 = true;
			}
			else if (b == 0 && cnt < krup[rk] && cnt > 21 && krup[rk] > 21)
			{
				std::cout << "Your score: " << cnt << " Draw" << std::endl;
				std::cout << "Dealer score: " << krup[rk] << std::endl;
				score2 = true;
			}
			else if (b == 0 && cnt == 21 && krup[rk] != 21)
			{
				std::cout << "Your score: " << cnt << " You win!!!" << std::endl;
				std::cout << "Dealer score: " << krup[rk] << std::endl;
				score3 = true;
			}
			else if (b == 0 && cnt != 21 && krup[rk] == 21)
			{
				std::cout << "Your score: " << cnt << " You lose" << std::endl;
				std::cout << "Dealer score: " << krup[rk] << std::endl;
				score1 = true;
			}
			else if (b == 0 && cnt == 21 && krup[rk] == 21)
			{
				std::cout << "Your score: " << cnt << " Draw!" << std::endl;
				std::cout << "Dealer score: " << krup[rk] << std::endl;
				score2 = true;
			}
			else if (b == 0 && cnt < krup[rk] && cnt < 21 && krup[rk] < 21)
			{
				std::cout << "Your score: " << cnt << " You lose" << std::endl;
				std::cout << "Dealer score: " << krup[rk] << std::endl;
				score1 = true;
			}
			else if (b == 0 && cnt > krup[rk] && cnt < 21 && krup[rk] < 21)
			{
				std::cout << "Your score: " << cnt << " You win!!!" << std::endl;
				std::cout << "Dealer score: " << krup[rk] << std::endl;
				score3 = true;
			}
			else if (b == 0 && cnt > 21 && krup[rk] > cnt)
			{
				std::cout << "Your score: " << cnt << " Draw" << std::endl;
				std::cout << "Dealer score: " << krup[rk] << std::endl;
				score2 = true;
			}
			else if (b == 0 && cnt > 21 && krup[rk] < cnt)
			{
				std::cout << "Your score: " << cnt << " You lose" << std::endl;
				std::cout << "Dealer score: " << krup[rk] << std::endl;
				score1 = true;
			}
			else if (b == 0 && cnt < krup[rk] && cnt < 21 && krup[rk] > 21)
			{
				std::cout << "Your score: " << cnt << " You win!!!" << std::endl;
				std::cout << "Dealer score: " << krup[rk] << std::endl;
				score3 = true;
			}
			//end 3-d
		}
		else
		{
			std::cout << "Your score: " << numbers[randomnum] << " You lose!" << std::endl;
			std::cout << "Dealer score: " << krup[rk] << std::endl;
			score1 = true;
		}
		//end 2-nd
	}
	//end 1-st

	//rec score in file
	//score1
	if (score1 == true)
	{
		file << timeString << lineNumber + 1 << ") The result of the game: " << "Lose" << "\n";
		file.close();
	}
	//end

	//score2
	if (score2 == true)
	{
		file << timeString << lineNumber + 1 << ") The result of the game: " << "Draw" << "\n";
		file.close();
	}
	//end

	//score3
	if (score3 == true)
	{
		file << timeString << lineNumber + 1 << ") The result of the game: " << "Win"  << "\n";
		file.close();
	}
	//end
	//end of rec

	return 1;
}