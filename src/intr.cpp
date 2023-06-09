#include "..\include\intr.h"


using namespace std;


int main()
{
	int action;
	cout << "Hello. It's Polinom Lab.\nYou can input your Polinom, save your Polionm and do simple ariphmetic with your Polinoms!";
	bool firstFlag = true;
	bool secondFlag = true;
	bool firdFlag = true;
	bool fourthFlag = true;
	bool flag = true;
	char name = ' ';
	vector<vector<char>> savedPolinomList(6);
	List<Polinom> polinomList;
	Expression expr;
	string inptExpresString;
	PolinomParse parsedStr;
	string polinomStr;
	Polinom inptPol;
	OrderedTable<char, Polinom> orderedTable;
	unordered_table<char, Polinom> unorderedTable;
	rbtTree<Polinom> rbTree;
	AVL_tree<char, Polinom> avlTree;
	HashTableOpenAdress<Polinom> hashTableOpenAdress;
	hash_table<string, Polinom> hashTableChain;
	while (firstFlag)
	{
		system("cls");
		cout << "To chose your action input number:\n0 - quit\n1 - work with Polinom\n2 - input Expression with Polinoms\n";
		cin >> action;
		switch (action)
		{
		case 0:
			firstFlag = false;
			system("cls");
			break;
		case 1:
			secondFlag = true;
			while (secondFlag)
			{
				system("cls");
				cout << "What you'l do:\n0 - quit\n1 - input Polinom\n2 - save Polinom\n3 - print data structs\n4 - input express with saved polinom and done it\n";
				cin >> action;
				switch (action)
				{
				case 0:
					secondFlag = false;
					system("cls");
					break;
				case 1:
					system("cls");
					cout << "Input Polinom name(0-to qiut): ";
					cin >> name;
					if (name == '0')
					{
						break;
					}
					cout << "Input Polinom : ";
					cin >> polinomStr;
					inptPol = Polinom(name, stringToMonomList(polinomStr));
					cout << "\nPolinom: " << inptPol << endl;
					while (fourthFlag)
					{
						cin >> action;
						if (action == 0)
						{
							fourthFlag = false;
						}
					}
					fourthFlag = true;
					break;
				case 2:
					system("cls");
					cout << "Chose data struct:\n0 - quit\n1-Ordered\n2-Unordered\n3-HashChain\n4-HashOpen\n5-Avl\n6-rbt\n";
					firdFlag = true;
					while (firdFlag)
					{
						cin >> action;
						switch (action)
						{
						case 0:
							firdFlag = false;
							system("cls");
							break;
						case 1:
							if (inptPol.empty())
							{
								cout << "\nWarning! Input your Polinom!";
							}
							else
							{
								//Ne rabotaet pochemyto, mb lowerbound
								savedPolinomList[0].push_back(name);
								orderedTable.push(name, inptPol);
							}
							firdFlag = false;
							break;
						case 2:
							if (inptPol.empty())
							{
								cout << "\nWarning! Input your Polinom!";
							}
							else
							{
								savedPolinomList[1].push_back(name);
								unorderedTable.push(name, inptPol);
							}
							firdFlag = false;
							break;
						case 3:
							if (inptPol.empty())
							{
								cout << "\nWarning! Input your Polinom!";
							}
							else
							{
								savedPolinomList[2].push_back(name);
								hashTableChain.insert({ string(1, name), inptPol });
							}
							firdFlag = false;
							break;
						case 4:
							if (inptPol.empty())
							{
								cout << "\nWarning! Input your Polinom!";
							}
							else
							{
								savedPolinomList[3].push_back(name);
								hashTableOpenAdress.push(name, inptPol);
							}
							firdFlag = false;
							break;
						case 5:
							if (inptPol.empty())
							{
								cout << "\nWarning! Input your Polinom!";
							}
							else
							{
								savedPolinomList[4].push_back(name);
								avlTree.insert(name, inptPol);
							}
							firdFlag = false;
							break;
						case 6:
							if (inptPol.empty())
							{
								cout << "\nWarning! Input your Polinom!";
							}
							else
							{
								savedPolinomList[5].push_back(name);
								rbTree.insert(name, inptPol);
							}
							firdFlag = false;
							break;
						default:
							break;
						}
					}
					break;
				case 3:
					system("cls");
					cout << "What struct you want print?\n0 - quit\n1-Ordered\n2-Unordered\n3-hashTableChain\n4-HashOpen\n5-Avl\n6-rbt\n";
					cin >> action;
					switch (action)
					{
					case 0:
						system("cls");
						break;
					case 1:
						orderedTable.print();
						cout << "\n";
						while (fourthFlag)
						{
							cin >> action;
							if (action == 0)
							{
								fourthFlag = false;
							}
						}
						fourthFlag = true;
						break;
					case 2:
						unorderedTable.print();
						cout << "\n";
						while (fourthFlag)
						{
							cin >> action;
							if (action == 0)
							{
								fourthFlag = false;
							}
						}
						fourthFlag = true;
						break;
					case 3:
						//hashTableChain.print();
						break;
					case 4:
						hashTableOpenAdress.print();
						cout << "\n";
						while (fourthFlag)
						{
							cin >> action;
							if (action == 0)
							{
								fourthFlag = false;
							}
						}
						fourthFlag = true;
						break;
					case 5:
						//avlTree.print();
						break;
					case 6:
						rbTree.print();
						cout << "\n";
						while (fourthFlag)
						{
							cin >> action;
							if (action == 0)
							{
								fourthFlag = false;
							}
						}
						fourthFlag = true;
						break;
					}
					break;
				case 4:
					system("cls");
					cout << "Input your polinom express: ";
					cin >> inptExpresString;
					if (inptExpresString == "0")
					{
						break;
					}
					for (int i = 0; i < 6; i++)
					{
						if (!savedPolinomList[i].empty())
						{
							switch (i)
							{
							case 0:
								for (char name : savedPolinomList[i])
								{
									polinomList.push_back((*(orderedTable.findElem(name))).second);
								}
								break;
							case 1:
								for (char name : savedPolinomList[i])
								{
									polinomList.push_back(unorderedTable[name]);
								}
								break;
							case 2:
								for (char name : savedPolinomList[i])
								{
									polinomList.push_back((*(hashTableChain.find(string(1, name)))).second);
								}
								break;
							case 3:
								for (char name : savedPolinomList[i])
								{
									polinomList.push_back(hashTableOpenAdress.findValue(name));
								}
								break;
							case 4:
								for (char name : savedPolinomList[i])
								{
									polinomList.push_back(avlTree[name]);
								}
								break;
							case 5:
								for (char name : savedPolinomList[i])
								{
									polinomList.push_back(rbTree.search(name)->value);
								}
								break;
							default:
								break;
							}
						}
					}
					expr = Expression(inptExpresString, polinomList);
					GetAnswerWithPolinom(expr);
					cout << '\n';
					while (flag)
					{
						cin >> action;
						if (action == 0)
						{
							flag = false;
						}
					}
				default:
					break;
				}
			}
			break;
		case 2:
			system("cls");
			cout << "Input your express(0 - to quit): \n";
			cin >> inptExpresString;
			if (inptExpresString == "0")
			{
				system("cls");
				break;
			}
			parsedStr = PolinomParse(inptExpresString);
			expr = Expression(parsedStr.getString(), parsedStr.getPolinomList());
			GetAnswerWithPolinom(expr);
			break;
		default:
			break;
		}

	}
	cout << "\nThanks for using, Buy!(\n";
}