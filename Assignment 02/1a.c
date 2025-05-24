#include <stdio.h>
#include <string.h>

struct paratha{
int quantity;
float price;}
;
struct vegetable{
int quantity;
float price;}
;
struct mineralwater{
int quantity;
float price;}
;
int main(){
struct paratha parathas;
struct vegetable vegetables;
struct mineralwater mineralwaters;

printf("Quantity Of Paratha: ");
scanf("%d",&parathas.quantity);
printf("Unit Price: ");
scanf("%f",&parathas.price);

printf("Quantity Of Vegetables: ");
scanf("%d",&vegetables.quantity);
printf("Unit Price: ");
scanf("%f",&vegetables.price);

printf("Quantity Of Mineral Water: ");
scanf("%d",&mineralwaters.quantity);
printf("Unit Price: ");
scanf("%f",&mineralwaters.price);

float total_bill= (parathas.quantity*parathas.price) +(vegetables.quantity*vegetables.price) + (mineralwaters.quantity*mineralwaters.price); 

int person;

printf("Number of People: ");
scanf("%d",&person);

float individual=total_bill/person;

printf("Individual people will pay: %.2f tk \n",individual);

return 0;
}
