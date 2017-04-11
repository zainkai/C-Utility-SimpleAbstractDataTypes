#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int TopPosition;
    int Capacity;
    void** Data;
} ADTStack;

ADTStack* ADTStackCreate(int Capacity)
{
    if(Capacity == 0){
        return NULL;
    }

    int i;

    ADTStack* obj = malloc(sizeof(ADTStack));
    obj->Data = malloc(Capacity * sizeof(void*));

    for(i = 0;i < Capacity; i++){
        obj->Data[i] = NULL;
    }

    obj->Capacity = Capacity;
    obj->TopPosition = 0;

    return obj;
}

void _ADTStackFreeData(void** Data, int MinIdx,int MaxIdx){
    int i;

    for(i = MinIdx; i < MaxIdx +1; i++){
        if(Data[i] != NULL){
            free(Data[i]);
        }
    }
}

void ADTStackFree(ADTStack* obj)
{
    if(obj == NULL){
        return;
    }  

    _ADTStackFreeData(obj->Data,0,obj->Capacity); 

    free(obj->Data);
    free(obj);
}

int ADTStackSize(ADTStack* obj){
    if(obj == NULL){
        return -1;
    }
    
    return obj->TopPosition;
}

void* ADTStackTop(ADTStack* obj)
{
    if(obj == NULL){
        return NULL;
    }

    return obj->Data[obj->TopPosition -1];
}

void* ADTStackPush(ADTStack* obj, void* item)
{
    if(obj == NULL){
        return NULL;
    }
    else if(obj->TopPosition == obj->Capacity -1){
        return NULL;
    }

    void* TempItem = malloc(sizeof(void*));
    memcpy(TempItem,item,sizeof(void*));
    obj->TopPosition++;

    return obj->Data[obj->TopPosition -1] = TempItem;
}

void ADTStackPop(ADTStack* obj){
    if(obj == NULL){
        return;
    }
    else if(obj->TopPosition < 0){
        return;
    }

    obj->TopPosition--;
    free(obj->Data[obj->TopPosition]);
    obj->Data[obj->TopPosition] = NULL;
}

ADTStack* ADTStackResize(ADTStack* obj, int NewCapacity)
{
    if(obj == NULL || NewCapacity < 0){
        return NULL;
    }

    int i;
    void** NewData = malloc(NewCapacity * sizeof(void*));
    
    for(i = 0; i < NewCapacity;i++){
        //swapping pointers to items.
        NewData[i] = obj->Data[i];
    }

    //check if offset is negative
    if((obj->Capacity - NewCapacity) < 0){
        if(obj->TopPosition > NewCapacity){
            obj->TopPosition -= NewCapacity; 
        }
        _ADTStackFreeData(obj->Data,NewCapacity,obj->Capacity);
    }

    free(obj->Data);
    obj->Data = NewData;
    obj->Capacity = NewCapacity;

    return obj;
}

int main()
{
    ADTStack* arr = ADTStackCreate(100);
    ADTStackResize(arr,50);

    int item1 = 1;
    ADTStackPush(arr,&item1);
    
    int temp = *(int*)ADTStackTop(arr);
    printf(":::%d\n",temp);

    ADTStackPop(arr);

    ADTStackFree(arr);
    return 0;
}