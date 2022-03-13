#include "ListQueue.h"
#include "LinkedList.h"
#include <iostream>
#include "Array1.h"
#include "BinarySearchTree.h"
#include <Windows.h>


//I couldn't really gather much from this, as I didn't really know what searching was.
//It can easily be assumed that one or the other types were faster at searching, I didn't know  how to make the same search function for all of them.
//Probably just reflects what we already learned from the lectures. 
using namespace std;
using namespace data_structures;

int search(const char A[], char value)
{
	int CharCount = 0;
	int x = 0;
	while (A[x] != '\0')
	{
		if (A[x] == value) ++CharCount;
		x++;
	}
	return CharCount;
}


int main()
{

	//ARRAY//
	int temp;

	bool pass = true;

	int num_elements = 10;  // Change this if test data changes
	int test_data[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

	Array<int> val_len(10);

	for (int i = 0; i < num_elements; ++i)
		val_len[i] = test_data[i];

	for (int i = 0; i < num_elements && pass; ++i)
	{
		temp = val_len[i];

		if (temp != test_data[i])
			pass = false;
		//ARRAY//

		char x;
		const char nameArray[] = { "nivke RyadiondqwmfiomopaOosadpsapdoasdsakopsaokasokfmweoieoifwemoiwemfowemoiwemfowemowemoifmweofmweomfweomfowemoiewmfiowemfoiwemofiwemfoiwemioewmfoiwemoifwemoifwemoifmweoifmweomfewoimfeoiwmfowiemfweoimaoimaoifmoiamfoaimfoaimfoamfomamoifamoimfaoifmaoimfaoimfaoimfaoimfoiamfaoamfoiamfoiamfoiamofiamoifimamoifamoifamofamfafmaoomafmoiafmoipopaskaopsopadkposoadkopaskfkewopfkewopkfoewkpowekfowekopewkfkeopwkfewopkfopwekopwekopewkpowewepkpowekfopwekfopwekfopwekopweopwekopfweopfweopfekopekopwekopwekfopwekfopwekopwekfopwekpofkweopkewkfweopkfopwekfopewkfpowekfopwekfopwekofkaaaaaaklfewmweffewoiwefoioifewiofweiojfweiowfeoiwfiowfeijowejoiaao" };
		// Enter the letter to search for
	
		x = 'a';
		// cout if it was found or not
		int start = GetTickCount64();
		int letterCount = search(nameArray, x);
		if (letterCount < 1)
			cout << "This letter was not found" << endl;
		else
			cout << "Found !, " << "it appears " << letterCount << " times in Your Name";

		int end = GetTickCount64() - start;
		std::cout << "\nTHE BOI\n" << endl; //4063
		std::cout << end << endl;

		BinarySearchTree<int> t1;
		t1.InOrderTraversal(0);


		//HASH//

		HashTable HT;

		if (HT.isEmpty()) {
			cout << "correct!" << endl;
		}
		else {
			cout << "EMPTY ERROR" << endl;
		};

		HT.Insert(903, "Barack");
		HT.Insert(202, "Tom");
		HT.Insert(407, "John");
		HT.Insert(604, "Boi");
		HT.Insert(206, "Barb");
		HT.Insert(507, "Rob");
		HT.Insert(507, "Rick"); //test to replace rob with rick

		HT.printTable();

		HT.removeItem(407);
		HT.removeItem(100);

		if (HT.isEmpty()) {
			cout << "UH OH" << endl;
		}
		else {
			cout << "NOT EMPTY, WOO!" << endl;
		};

		//HASH//
		

	}

}