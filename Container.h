//
// Created by Дмитрий on 12.05.2020.
//

#ifndef INTERFACETREE_CONTAINER_H
#define INTERFACETREE_CONTAINER_H


// Обновлённый интерфейс, теперь он шаблон
template<typename T>
class Container
{
public:
    // Виртуальный деструктор
    virtual ~Container() {};

    /*
     * Виртуальные методы, должны быть реализованы вашим контейнером
     */

    // Вставка элемента
    virtual void insert(const T& value) = 0;

    // Удаление элемента
    virtual void remove(const T& value) = 0;

    // Проверка наличия элемента
    virtual bool exists(const T& value) const = 0;
};
#endif //INTERFACETREE_CONTAINER_H
