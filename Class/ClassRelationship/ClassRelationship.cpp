#include <iostream>

class Engine
{

};

class Tire
{

};

class Driver
{

};

class Car
{
    // A is-part-of B (Composition)
    // A는 B의 구성요소
    // A는 한번에 하나의 객체에만 존재
    // A는 B에 의해 관리됨
    // A는 B의 내용을 알 수 없음
    Engine mEngine;

    // A has-a B (Aggregation)
    // B는 A의 구성요소
    // B는 여러 객체에 소속될 수 있음
    // B는 A에 의해 관리되지 않음
    // B는 A의 내용을 알 수 없음
    Tire *pTire;

    // A use-a B (Assocication)
    // B는 A와 관련이 없음
    // B는 여러 객체에 소속될 수 있음
    // B는 A에 의해 관리할수도 있고, 아닐 수도 있음
    // B는 A의 내용을 알 수도 있고, 모를 수도 있음
    Driver *p;
};

/*
Driver me;
me.Use(Car);
*/

int main()
{
    Tire A = new Tire;

    Tire A;
    Car a;
    Car b;
    a.pTire = A;
}
