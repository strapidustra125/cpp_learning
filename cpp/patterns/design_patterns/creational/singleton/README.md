
# Singleton (Одиночка)

Порождающий паттерн. С помощью него обеспечивается наличие единственного экземпляра класса с глобальной точкой доступа в многопоточном приложении.

![UML диаграмма паттерна](pictures/singleton.jpg)

## Пример реализации (надстройка над синглтоном Майерса):

```c++
class Singleton
{

public:

    // Ссылка на синглтон для работы с ним: "Singleton & instance = Singleton::Instance();"

    // Также возможно создание статического поля _instance в теле класса
    // Разница будет в том, что статическое поле класса создастся сразу, а не при первом вызове
    // функции instance()

    static Singleton & instance()
    {
        // Согласно стандарту, этот код ленивый и потокобезопасный, т.к. static распространяется на
        // потоки.
        // Т.е. при вызове метода instance() гарантированно создастся только один объект в одном
        // потоке. Остальные будут ждать и не будут плодить свои копии объекта.

        // Это называется - отложенная инициализация
        // Т.е. экземпляр создастся только тогда, когда его первый раз вызовут
        static Singleton s;
        return s;
    }

private:

    // Конструктор и деструктор недоступны пользователю, но реализуют какую-то логику
    Singleton() {}
    ~Singleton() {}

    // Оператор присваивания и конструктор копирования не нужны.
    // Т.к. во многих случаях они создаются компилятором «за вашей спиной».
    // Чтобы никто не мог ими воспользоваться, нужно задекларировать их приватными или (с С++11)
    // убрать при помощи конструкции «= delete».
    Singleton(const Singleton &) = delete;
    Singleton & operator= (const Singleton &) = delete;

    // В операторах сравнения нет нужды, так как всё равно есть лишь один экземпляр.
    // Поскольку автоматически операторы сравнения не создаются, вам не нужно ни о чём беспокоиться.
};
```

## Применение паттерна

Паттерн Singleton хорош всегда, когда важно гарантировать, что создан **только один** объект класса (это его первостепенная задача): одно подключение, один сборщик диагностики. Т.е. всегда, когда можно использовать статический класс.

Практические примеры задач, где подойдет этот паттерн:

- Конфигурация.

    Настройки приложения нужны только в одном экземпляре. Особенно удобно, если они читаются на старте работы программы и больше не трогаются.

- Подключение к БД.

    Для работы с БД важно иметь только одно подключение к базе, чтобы избежать траты лишних ресурсов.

- Логирование.

- Статистика и диагностика приложения.

## Сравнение паттерна Singleton и статического класса

Основное отличие заключается в том, что у синглтона существует **только один** объект, а у статического класса - **ни одного**.

Примеры:

- Количество точек доступа

    У синглтона - только одна точка доступа (через представление), а у статического класса - каждый метод - точка доступа.

- Наследование

    Статический класс невозможно наследовать. А синглтон можно сделать шаблоном, чтобы наследовать от него любые другие классы, которые будут синглтонами, но без повторяющегося кода создания представления и доступа к нему.

    ```c++
    // Создается шаблонный класс, от которого будут наследоваться другие синглтоны
    // При объявлении, наследуемый класс вместо T подставляет свое имя
    // Также наследующий класс должен объявить свои конструкторы защищенными и добавить Singleton
    // в друзья: friend class Singleton<Config>;
    template <class T>
    class Singleton
    {

    protected:

        // Конструктор по умолчанию защищенный, чтобы он был доступен только в наследниках, но не
        // был доступен пользователю
        Singleton()     = default;
        ~Singleton()    = default;

    public:

        // Ссылка на представление класса
        static T & instance()
        {
            static T instance;
            return instance;
        }

        Singleton(const Singleton &)                = delete;
        Singleton & operator= (const Singleton &)   = delete;

    };
    ```

- Передача в качестве параметра

    Синглтон можно передать в качестве параметра, т.к. есть экземпляр класса. Статический класс нельзя по обратной причине.

- Сериализация

    Та же причина: наличие экземпляра класса. Синглтон можно сериализировать, а статический класс - нет.

- Передача в фабрику

    Та же причина: наличие экземпляра класса. Синглтон можно передать в фабрику, а статический класс - нет.


## Плюсы и минусы паттерна

**(+) Плюсы**

- Гарантированное наличие одного экземпляра объекта. Идеален для конфигурации приложения. Особенно, если она не меняется во время работы.


**(-) Минусы**

- Доступность из любого места программы. Значит сломать его может что угодно.

- Unit-тестирование.

    Нельзя создать сколько угодно копий объекта для тестирования. Синглтон добавляет в программу глобальную связанность, что мешает изолировать классы друг от друга. В таком случае было бы идеально сделать свойство быть синглтоном - опциональным.

- Скрытые зависимости.

    Самый явный способ передачи зависимостей - через конструктор объекта. У синглтона он не вызывается и непонятно, что нужно ему для работы.

## Резюме

Паттерн может быть использован только тогда, когда железно нужен только один экземпляр класса. Или если его минусы не релевантны. Т.е. приложение не покрыто юнит тестами и зависимостей у синглтона нет.

*Лучшим применением паттерна является единожды читаемая конфигурация приложения.*
