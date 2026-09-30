#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

void add_item(Item *item_list, double price, char *sku, char *category, char *name, int index){

	//Allocation for the components	
	item_list[index].name = malloc(strlen(name)+1);
	if(item_list[index].name == NULL){
		printf("Allocation for name failed");
		return;
	}

	
	item_list[index].sku = malloc(strlen(sku)+1);
	if(item_list[index].sku == NULL){
		printf("Allocation for SKU failed");
		return;
	}

	item_list[index].category = malloc(strlen(category)+ 1);
	if(item_list[index].category == NULL){
		printf("Allocation for category failed");
		return;
	}

	//Have to use string copy, or else freeing will get complicated
	
	item_list[index].price = price;
	strcpy(item_list[index].name, name);
	strcpy(item_list[index].sku, sku);
	strcpy(item_list[index].category, category);
}


void free_items(Item *item_list, int size){
	for(int i = 0; i < size; i++){
		free(item_list[i].name);
		item_list[i].name = NULL;
		free(item_list[i].sku);
		item_list[i].sku = NULL;
		free(item_list[i].category);
		item_list[i].category = NULL;
	}
}

double average_price(Item *item_list, int size){
	double average = 0;
	for(int i = 0; i<size; i++){
		average = average + item_list[i].price;
	}
	average = average/size;
	return average;
}

void print_items(Item *item_list, int size){
	printf("\n-----------------\n");
	printf("ITEM %d\n", size + 1);
	printf("Article Name: %s\n", item_list[size].name);
	printf("Price: $%.2f\n", item_list[size].price);
	printf("SKU: %s\n", item_list[size].sku);
	printf("Category: %s\n", item_list[size].category);
}



int main(int arguments, char *argv[]){

	//Taking only 2 arguments
	if(arguments != 2){
		printf("only 2 arguments please");
		return 1;
	}


	//Allocating for 5 structs
	Item *pItem = malloc(sizeof(Item)*5);
	if(pItem == NULL){
		printf("memory allocation of pItem failed");
		return 1;
	}

	//Assigning Items
	//ITEM 1 --> MACBOOK
	add_item(pItem, 350.99, "10000", "electronics", "Macbook", 0);
	print_items(pItem, 0);
	
	//ITEM 2 --> AIRPODS
	add_item(pItem, 170.99, "10001", "electronics", "Airpods", 1);
	print_items(pItem, 1);
	
	//ITEM 3 --> POKEMON CARDS
	add_item(pItem, 19.99, "15123", "collectibles", "Pokemon Cards", 2);
	print_items(pItem, 2);
	
	//ITEM 4 --> APPLE
	add_item(pItem, 0.50, "00112", "produce", "Apple", 3);
	print_items(pItem, 3);

	//ITEM 5 --> Desk Chair
	add_item(pItem, 79.99, "20032", "furniture", "Desk Chair", 4);
	print_items(pItem, 4);

	//AVERAGE
	double totalAverage = average_price(pItem, 5);
	printf("\n\nAverage price of all items: $%.2f\n\n", totalAverage);

	//SKU LOOKUP (Command Line)
	/*Apparently the second while command will cause out of bounds (segmentation fault: core dumped) */
	
	int ct = 0;
	while (ct < 5 && strcmp(pItem[ct].sku, argv[1]) != 0){
		printf("\nSKU does not match %s, %s\n", pItem[ct].sku, pItem[ct].name); 
		ct++;
	}	
	if(ct < 5){
		printf("****** SKU FOUND: %s, %s, %s ******\n\n\n", pItem[ct].sku, pItem[ct].name, pItem[ct].category);
	}


	//FREEING MEMORY
	for(int i = 0; i < 5; i++){
		free_items(pItem, i);
	}
	free(pItem);
	pItem = NULL;

return 0;
}

