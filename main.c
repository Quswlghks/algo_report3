#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "RBtree.h"
#include "AdjList.h"

int reserve_check_number;

void squre_box_print();
void random_reserve(RBtree t);
void source_name();
void destination_name();
void source_date();
void seat_print(RBtree t, char start, char dest);
int seatCheck(RBtree t, char start, char dest, int row, int col);

int main() {
	srand(time(NULL));
	RBtree t = RBtree_create();
	random_City_Position(city);
	random_reserve(t);
	make_AdjList();
	int choose_number;

	printf("***********************************************************************************************************************\n");

	printf("Red-Black tree height : %d \n", RBtree_height(t->root));
	printf("Red-Black tree  count node : %d\n ", count_node(t->root));

	while (1) {
		printf("***********************************\n");
		printf("    해당하는 숫자를 입력하세요!\n");
		printf("\n    ***  여행지를 선택 : 1 ***\n");
		printf("\n     ***  예약 조회 : 2  *** \n");
		printf("\n     ***  예약 취소 : 3  *** \n");
		printf("\n     ***  종료   : -1  *** \n\n");
		printf("\n***********************************\n");

		int  flag;
		do {
			flag = 0;
			printf("  -> ");

			if (!scanf(" %d", &choose_number)) {
				printf("숫자가 아닙니다. \n\n");
				flag = 1;
				while (getchar() != '\n');
			}
		} while (flag);

		if (choose_number == 1) {
			int reserve_number;
			int temp_date_check = 0;
			char station;
			char arrive;
			int flight_day = 0;

			for (int j = 0; j < 2; j++) {
				if (j == 0) {
					source_name();
					printf("-> ");
					scanf("  %c", &reservation[reserve_check_number].source);
					if (!isalpha(reservation[reserve_check_number].source)) {
						while (1) {
							printf("문자로 입력해주세요! \n");
							printf("-> ");
							scanf("  %c", &reservation[reserve_check_number].source);
							if (isalpha(reservation[reserve_check_number].source))
								break;
						}
					}
					station = reservation[reserve_check_number].source;
					printf("\n");

					squre_box_print();
					source_date();


					int  flag0;
					do {
						flag0 = 0;
						printf("  -> ");

						if (!scanf("%d", &temp_date_check)) {
							printf("숫자가 아닙니다. \n\n");
							flag0 = 1;
							while (getchar() != '\n');
						}
					} while (flag0);

					if (temp_date_check > 31 || temp_date_check < 0) {
						while (1) {
							printf("날짜를 다시 입력하세요!\n");

							int  flag5;
							do {
								flag5 = 0;
								printf("  -> ");

								if (!scanf("%d", &temp_date_check)) {

									printf("숫자가 아닙니다. \n\n");
									flag5 = 1;
									while (getchar() != '\n');
								}
							} while (flag5);

							if (temp_date_check <= 31 && temp_date_check > 0) break;
						}

					}


					else {
						reservation[reserve_check_number].date = temp_date_check;
						flight_day = reservation[reserve_check_number].date;

						PrintListTime(station, flight_day);
					}

				}

				else {
					destination_name();
					PrintList(station);
					printf("-> ");
					scanf(" %c", &reservation[reserve_check_number].destination);
					if (!isalpha(reservation[reserve_check_number].destination)) {
						while (1) {
							printf("문자로 입력해주세요!\n ");
							printf("-> ");
							scanf("  %c", &reservation[reserve_check_number].destination);
							if (isalpha(reservation[reserve_check_number].destination))
								break;
						}
					}
					arrive = reservation[reserve_check_number].destination;
					printf("\n");

				}
			}

			seat_print(t, station, arrive);
			printf(" \n -> 좌석을 선택해주세요! \n\n");
			printf(" -> ");
			char seat[3];
			scanf(" %s", &reservation[reserve_check_number].seat);
			strcpy(seat, reservation[reserve_check_number].seat);

			if(!(!seatCheck(t, station, arrive, seat[0] - 'A', seat[1] - '0') && ((seat[0] >= 'A' && seat[0] <= 'J') && (seat[1] >= '0' && seat[1] <= '6')))){
				do {
					printf("\n 좌석을 다시 입력하세요!\n");
					printf("\n-> ");
					scanf(" %s", &reservation[reserve_check_number].seat);
					strcpy(seat, reservation[reserve_check_number].seat);
				} while (!(!seatCheck(t, station, arrive, seat[0] - 'A', seat[1] - '0') && ((seat[0] >= 'A' && seat[0] <= 'J') && (seat[1] >= '0' && seat[1] <= '6'))));
			}

			printf("\n");
			printf(" \n -> 원하시는 좌석 등급을 선택해주세요! \n");
			printf(" \n 1 : prestige class  ( 가격  :  $3100 ) \n\n");
			printf(" \n 2 : business class ( 가격 :  $1100 )\n\n");
			printf(" \n 3 : economy class ( 가격 :  $700 )\n\n");
			printf(" -> ");
			scanf(" %d", &reservation[reserve_check_number].seat_level);
			if (reservation[reserve_check_number].seat_level < 0 || reservation[reserve_check_number].seat_level >3) {
				while (1) {
					printf(" 잘못입력하였습니다!\n ");
					printf(" -> ");
					scanf(" %d", &reservation[reserve_check_number].seat_level);
					if (reservation[reserve_check_number].seat_level > 0 && reservation[reserve_check_number].seat_level <= 3)
						break;
				}
			}

			printf(" \n -> 예약 하시겠습니까? \n");

			printf(" 1  : 예 \n");
			printf(" 2  : 아니오\n\n");

			int  flag1;
			do {
				flag1 = 0;
				printf("  -> ");

				if (!scanf("%d", &reserve_number)) {
					printf("숫자가 아닙니다. \n\n");
					flag1 = 1;
					while (getchar() != '\n');
				}
			} while (flag1);

			if (reserve_number == 1) {

				printf("이름 : ");
				scanf("%s", reservation[reserve_check_number].name, 10);
				printf("┏");
				for (int i = 0; i < 30; i++) printf("━");
				printf("┓\n");
				printf("┃ ");
				printf(" 예약을 완료하였습니다.");
				printf("      ┃ \n");
				printf("┃");
				printf("  예약 번호는  %d번  입니다.", reserve_check_number);
				if (reserve_check_number >= 10 && reserve_check_number < 100)
					printf("     ┃ \n");
				else if (reserve_check_number >= 100)
					printf(" ┃ \n");
				else
					printf(" ┃ \n");

				printf("┗");
				for (int i = 0; i < 30; i++) printf("━");
				printf("┛\n\n");
				reservation[reserve_check_number].reservation_num = reserve_check_number;

				array_RBTree[reserve_check_number] = reserve_check_number;
				RBtree_insert(t, (void*)array_RBTree[reserve_check_number], compare_int);
				reserve_check_number++;
				printf("Red-Black tree height : %d \n", RBtree_height(t->root));
				printf("Red-Black tree  count node : %d\n ", count_node(t->root));

			}
		}
		else if (choose_number == 2) {
			int check = 0;
			printf("예약 번호를 입력하세요 -> ");

			int  flag2;
			do {
				flag2 = 0;

				if (!scanf("%d", &check)) {
					printf("숫자가 아닙니다. \n\n");
					flag2 = 1;
					while (getchar() != '\n');
				}
			} while (flag2);

			if (RBtree_search_node(t->root, check) != NULL) {
				printf("┏");
				for (int i = 0; i < 28; i++) printf("━");
				printf("┓\n");
				printf("┃");
				printf(" 예약 번호 : %d", reservation[check].reservation_num);
				if (reservation[check].reservation_num >= 10 && reservation[check].reservation_num < 100)
					printf("             ┃ \n");
				else if (reservation[check].reservation_num >= 100)
					printf("             ┃ \n");
				else
					printf("              ┃ \n");
				printf("┃ ");
				printf("고객 이름 : %s", reservation[check].name);
				for (int i = 0; i < 28 - (13 + strlen(reservation[check].name)); i++) 	printf(" ");
				printf("┃ \n");

				printf("┃ ");
				printf("출발지    : %c", reservation[check].source);
				printf("	             ┃ \n");

				printf("┃ ");
				printf("도착지    : %c", reservation[check].destination);
				printf("	             ┃ \n");

				printf("┃ ");
				printf("출발날짜  : %d", reservation[check].date);
				if (reservation[check].date >= 10)
					printf("             ┃ \n");
				else
					printf("              ┃ \n");
				printf("┃ ");
				printf("좌석 번호 : %s", reservation[check].seat);
				printf("             ┃ \n");
				printf("┃ ");
				printf("좌석 등급 : ");
				if (reservation[check].seat_level == 1) {
					printf("prestige class");
					printf(" ┃ \n");
				}
				else if (reservation[check].seat_level == 2) {
					printf("business class");
					printf(" ┃ \n");
				}
				else {
					printf("economy class");
					printf("  ┃ \n");
				}
				printf("┃ ");
				int pathnum = shortest_path(reservation[check].source, reservation[check].destination, reservation[check].date);
				printf("기차시간  : %d ", pathnum);
				if (reservation[check].date > 10)
					printf("            ┃ \n");
				else if (reservation[check].date <= 10)
					printf("             ┃ \n");
				printf("┗");
				for (int i = 0; i < 28; i++) printf("━");
				printf("┛\n\n");
				if (pathnum >= 1000) {
					printf("\n\n-*-WARNING/ 올바르지 않은 예약입니다!!!(경로 없음)-*-\n\n");
					continue;
				}
				print_path(reservation[check].source, reservation[check].destination);
				print_time(reservation[check].date);


			}

			else if (RBtree_search_node(t->root, check) == NULL) {
				printf("┏");
				for (int i = 0; i < 28; i++) printf("━");
				printf("┓\n");
				printf("┃ ");
				printf("조회되지 않는 번호 입니다!");
				printf(" ┃ \n");
				printf("┗");
				for (int i = 0; i < 28; i++) printf("━");
				printf("┛\n\n");
			}
		}
		else if (choose_number == 3) {
			int check;
			printf("예약 번호를 입력하세요 -> ");

			int  flag3;
			do {
				flag3 = 0;

				if (!scanf("%d", &check)) {
					printf("숫자가 아닙니다. \n\n");
					flag3 = 1;
					while (getchar() != '\n');
				}
			} while (flag3);

			if (RBtree_search_node(t->root, check) != NULL) {
				RBtree_delete(t, (void*)check, compare_int);
				printf("┏");
				for (int i = 0; i < 25; i++) printf("━");
				printf("┓\n");
				printf("┃ ");
				printf("예약이 취소되었습니다!");
				printf("  ┃ \n");
				printf("┗");
				for (int i = 0; i < 25; i++) printf("━");
				printf("┛\n\n");
				printf("Red-Black tree height : %d \n", RBtree_height(t->root));
				printf("Red-Black tree  count node : %d\n ", count_node(t->root));
			}
			else printf("조회되지 않는 번호 입니다.\n\n");

		}

		else  if (choose_number != -1 && choose_number > 4) {
			printf("다시 입력해주세요 !\n\n\n ");
		}
		if (choose_number == -1) {
			printf("조회를 종료합니다!\n");
			printf("Red-Black tree height : %d \n", RBtree_height(t->root));
			printf("Red-Black tree  count node : %d \n\n", count_node(t->root));
			exit(1);
		}

	}

	return 0;

}

void squre_box_print() {
	printf("┏");
	for (int i = 0; i < 12; i++) printf("━");
	printf("┓\n");
	printf("┃");
	printf("  출발 날짜 ");
	printf("┃ \n");
	printf("┗");
	for (int i = 0; i < 12; i++) printf("━");
	printf("┛\n");

	int i = 0;
	int start = 0;
	const char* wname[7] = { "일","월","화","수","목","금","토" };

	printf("                   << 2024년 6월>>\n");
	printf("======================================================\n");
	printf("");
	for (i = 0; i < 7; i++)
	{
		printf("%7s", wname[i]);
	}
	printf("\n");
	for (i = 0; i < start; i++)
	{
		printf("%7s", " ");
	}
	for (i = 0; i < 31; i++)
	{
		printf("%7d", i + 1);
		start++;
		if (start == 7)
		{
			start = 0;
			printf("\n");
		}
	}
	printf("\n======================================================\n");
}

void source_date() {
	printf("┏");
	for (int i = 0; i < 30; i++) printf("━");
	printf("┓\n");
	printf("┃ ");
	printf("  출발 날짜를 입력해주세요!");
	printf("  ┃ \n");
	printf("┗");
	for (int i = 0; i < 30; i++) printf("━");
	printf("┛\n\n");
}

void source_name() {
	printf("┏");
	for (int i = 0; i < 44; i++) printf("━");
	printf("┓\n");
	printf("┃ ");
	printf("출발 할  도시를 입력해주세요!");
	printf("              ┃ \n");
	printf("┃ ");
	printf("'a'부터 'z'사이에서 선택해 주세요!");
	printf("         ┃ \n");
	printf("┗");
	for (int i = 0; i < 44; i++) printf("━");
	printf("┛\n\n");
}

void destination_name() {
	printf("┏");
	for (int i = 0; i < 44; i++) printf("━");
	printf("┓\n");
	printf("┃ ");
	printf("       도착 할  도시를 입력해주세요!");
	printf("       ┃ \n");
	printf("┗");
	for (int i = 0; i < 44; i++) printf("━");
	printf("┛\n\n");
}

void random_reserve(RBtree t) {
	char* cusname = (char*)malloc(sizeof(char) * 10);
	char* cuspos = (char*)malloc(sizeof(char) * 3);
	char alpha = 'a';
	for (int i = 0; i < 500; i++) {
		int namelen = rand() % 7 + 1;
		int start = rand() % 26;
		int arrive = rand() % 26;
		int sdate = rand() % 26;
		for (int j = 0; j < namelen; j++) {
			alpha = rand() % 26 + 'a';
			cusname[j] = alpha;

		}
		cusname[namelen] = '\0';
		for (int j = 0; j < 2; j++) {
			if (j == 0)
				cuspos[j] = rand() % 10 + 'A';
			else
				cuspos[j] = rand() % 7 + '0';
		}
		cuspos[2] = '\0';
		strcpy(reservation[reserve_check_number].name, cusname);
		strcpy(reservation[reserve_check_number].seat, cuspos);
		reservation[reserve_check_number].source = (char)(start + 'a');
		reservation[reserve_check_number].destination = (char)(arrive + 'a');
		reservation[reserve_check_number].date = sdate + 1;
		reservation[reserve_check_number].reservation_num = reserve_check_number;
		array_RBTree[reserve_check_number] = reserve_check_number;
		RBtree_insert(t, (void*)array_RBTree[reserve_check_number], compare_int);
		reserve_check_number++;
	}
}

void seat_print(RBtree t, char start, char dest) {
	printf("\t    좌석 정보\n");
	printf("   ┏");
	for (int i = 0; i < 25; i++) printf("━");
	printf("┓\n");
	printf("   ┃   0 1   2 3 4   5 6     ┃\n");
	for (int i = 0; i < 10; i++) {
		printf("   ");
		printf("┃   ");
		for (int j = 0; j < 7; j++) {
			if (j % 10 == 2 || j % 10 == 5)
				printf("┃ ");
			if (!seatCheck(t, start, dest, 9 - i, j)) {
				printf("o ");
			}
			else {
				printf("x ");
			}
		}
		printf(" %c", 'J' - i);
		printf("  ┃");
		printf("\n");
	}
	printf("   ┗");
	for (int i = 0; i < 25; i++) printf("━");
	printf("┛\n");
}

int seatCheck(RBtree t, char start, char dest, int row, int col) {
	for (int i = 0; i < reserve_check_number; i++) {
		if ((reservation[i].source == start) && (reservation[i].destination == dest)) {
			if ((reservation[i].seat[0] - 'A' == row) && (reservation[i].seat[1] - '0' == col)) {
				return 1;
			}
		}
	}
	return 0;
}