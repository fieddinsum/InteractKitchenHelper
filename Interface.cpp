#pragma once
#include"Interface.h"
#include<iostream>
#include<ctime>
using namespace std;


Interface::Interface() {
	
	//loadFileData(dataBase, planmanager);
	frontImage.printImage();		// 초기화면 출력
	showTodayInformation();
}

void Interface::printTitleMenu() {

	string line;
	ifstream inFile("Titlemenu.txt", ios::in);

	if (inFile.is_open()) {
		while (getline(inFile, line)) {
			system("Color 78");
			std::cout << line;
		}
		inFile.close();
	}
}

void Interface::showFrontMenu() {

	int userInput = 0;

	std::cout << "=================IIKH System Menu =============" << std::endl;
	std::cout << "1.레서피 검색 2.레서피 추가 3. 레서피 수정 " << std::endl;
	std::cout << " 4.레서피 삭제 5. 모든 레시피 종류 보기" << std::endl;
	std::cout << "6. 일정/식단 보기 7. 일정/식단 수정 8. 상태저장" << std::endl;
	std::cout << "9. 프로그램 종료" << std::endl;
	std::cout << "=================IIKH System Menu =============" << std::endl;
	std::cout << "번호를 입력하세요 : ";

	std::cin >> userInput;
	cin.clear();
	cin.ignore(10000, '\n');
	std::cout << std::endl;


	switch (userInput)
	{
	case 1:
		dataBase.searchRecipe();
		break;
	case 2:
		dataBase.addRecipe();
		break;
	case 3:
		dataBase.modifyRecipe();
		break;
	case 4:
		dataBase.deleteRecipe();
		break;
	case 5:
		dataBase.showAllRecipeList();
		break;
	case 6:
		// 일정/식단 보기
		showDayPlan();
		break;
	case 7:
		// 일정/식단 수정
		editDayPlan();
		break;
	case 8:
		// 현재 상태 저장 
		saveFileData(this->dataBase, this->planmanager);
		break;
	case 9:
		exit(1);
		break;
	default:
		break;
	}


}


void Interface::showDayPlan() {

	int date, menunum = 0;
	std::cout << "확인할 날짜를 입력하세요(1~30) : ";
	std::cin >> date;

	while (date<1 || date>30) {
		cout << "날짜를 잘못입력하셨습니다. 확인할 날짜를 입력하세요 : ";
		std::cin >> date;
	}

	planmanager.showDailyPlan(date);

	while (menunum != 4) {
		std::cout << "1.아침메뉴 상세보기  2.점심메뉴 상세보기" << std::endl << "3.저녁메뉴 상세보기 4.상위메뉴로 돌아가기 " << std::endl << "해당하는 숫자를 입력하세요 : ";
		std::cin >> menunum;

		if (menunum == 4)
			showFrontMenu();

		else {
			while (menunum <1 || menunum > 3) {
				if (menunum == 4){
					showFrontMenu();
				}
				else {
					std::cout << "숫자를 잘못입력하셨습니다." << std::endl;
					std::cout << "1.아침메뉴 상세보기  2.점심메뉴 상세보기" <<std::endl<< "3.저녁메뉴 상세보기 4.상위메뉴로 돌아가기" << std::endl << "해당하는 숫자를 입력하세요 : ";
					std::cin >> menunum;
				}

			}
		}

		switch (menunum) {
		case 1:
			if (planmanager.getOneDay(date).getMealName(1).compare("아침없음") == 0) {
				std::cout << "확인할 메뉴가 없습니다." << std::endl;

			}
			else {
				std::cout << planmanager.getOneDay(date).getMealNumber(1) << "명분의 요리를 해야합니다." << std::endl;
				dataBase.showRecipeOfDish(planmanager.getOneDay(date).getMealName(1));
			}
			break;

		case 2:
			if (planmanager.getOneDay(date).getMealName(2).compare("점심없음") == 0) {
				std::cout << "확인할 메뉴가 없습니다." << std::endl;
			}
			else{
				std::cout << planmanager.getOneDay(date).getMealNumber(2) << "명분의 요리를 해야합니다." << std::endl;
				dataBase.showRecipeOfDish(planmanager.getOneDay(date).getMealName(2));
			}
			break;

		case 3:
			if (planmanager.getOneDay(date).getMealName(3).compare("저녁없음") == 0) {
				std::cout << "확인할 메뉴가 없습니다." << std::endl;
			}
			else{
				std::cout << planmanager.getOneDay(date).getMealNumber(3) << "명분의 요리를 해야합니다." << std::endl;
				dataBase.showRecipeOfDish(planmanager.getOneDay(date).getMealName(3));
			}
			break;

		default:
			break;
		}

	}
}


void Interface::editDayPlan()
{
	int day;
	int menu;	// 콘솔메뉴
	Day myDay;
	string newMenu;	// 수정할 메뉴명
	int newNumber;	// 수정할 인원수
	string newPlan;	// 수정할 플랜

					/* 1. 날짜 입력 */
	while (1)
	{
		cout << "<< 일정/식단 수정 >>" << endl << "날짜를 입력하세요(1 ~ 31) : ";
		cin >> day;

		if (1 <= day && day <= 31)
			break;
		else
			cout << "1에서 31 사이의 수만 입력하세요" << endl;
	}
	myDay = planmanager.getOneDay(day);
	std::cout << day << "일 ";
	myDay.showTodayData();


	/* 2. 메뉴 */
	while (1)
	{
		cout << endl << "1. 아침메뉴 수정하기" << endl
			<< "2. 점심메뉴 수정하기" << endl
			<< "3. 저녁메뉴 수정하기" << endl
			<< "4. 일정추가하기" << endl
			<< "5. 일정삭제하기" << endl
			<< "6. 상위메뉴로" << endl
			<< "Input : ";

		fflush(stdin);
		cin >> menu;

		/* 메뉴수정파트 */
		if (menu == 1 || menu == 2 || menu == 3)
		{
			cout << endl << " 1 > 메뉴명 수정" << endl;
			newMenu = dataBase.selectOneRecipeName();
			myDay.setMealName(menu, newMenu);

			cout << endl << " 2 > 식사인원 수정 : ";
			cin >> newNumber;
			myDay.editNumber(menu, newNumber);
		}

		/* 일정수정파트 */
		else if (menu == 4)
		{
			cout << endl << " > 일정추가" << endl;
			fflush(stdin);
			std::getline(std::cin, newPlan);
			myDay.addPlan(newPlan);
		}
		else if (menu == 5)
		{
			myDay.deleteAllPlan();
		}

		/* 기타 */
		else if (menu == 6)
		{
			return;
		}
		else
		{
			cout << "잘못된 입력입니다" << endl;
		}

		planmanager.changeDay(myDay, day);
	}
}

void Interface::showTodayInformation() {


}

void Interface::loadFileData(DataBase &dataBase, PlanManager &planmanager){
   //한달 Day 정보를 프로그램에 불러옴
   Day loadDay;
   FILE* datefptr;
   datefptr = fopen("saveDayData.txt", "r");

   int date = 1;
   while (date < 32) {
      ifstream ifp(datefptr);
      char line[128];
      int count = 0;
      char* context = NULL;
      while (fgets(line, 128, datefptr) != NULL){

         cout << line << endl;
         char* token = strtok_s(line, ",", &context);
         if (token != NULL){//Number
         //★/  loadDay.editNumber = token - 48; //맨 앞은 숫자이기 때문에 -48해줌
		// editNumber(int time, int newNumber) 는 함수인데
		// 처음에 받는 숫자는 몇일에 이걸 넣을지 인데 어떤식으로 쓰겠다는건지 
		// 수정필요함
         }
         while (token){
            count++;
            token = strtok_s(NULL, ",", &context);
            if (count == 1){//아침메뉴


            }
            else if (count == 2){//점심메뉴

            }
            else if (count == 3){//저녁메뉴

            }
            else if (count == 4){//아침 인원 수


            }
            else if (count == 5){//점심 인원 수


            }
            else if (count == 6){//저녁 인원 수

            }
            else if (count == 7){//오늘일정1

            }
            else if (count == 8){//오늘일정2

            }
            else if (count == 9){//오늘일정3

               count = 0;
               break;
            }
         }
      } //한줄씩 읽으면서 파싱


   }

      fclose(datefptr);

}


void Interface::saveFileData(DataBase &dataBase, PlanManager &planmanager){
	//한달 Day 정보를 파일에 저장함
	planmanager.saveMonthPlan();
	// 현재 레서피 정보를 파일에 저장함 
	dataBase.saveDataBase();
}