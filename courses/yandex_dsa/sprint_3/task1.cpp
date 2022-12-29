/**************************************************************************
 *
 * Успешная попытка: 79877371
 *
 * -- ПРИНЦИП РАБОТЫ --
 *
 *  Массив:
 * Массив отсортированный, но сдвинутый, поэтому при делении пополам одна
 * из половин окажется отсортированной, а вторая нет. Критерий 
 * отсортированности (под)массива - левый край меньше правого.
 * Если массив отсортирован - обычный бинарный поиск. Если нет - деление 
 * пополам и проверка половин. Если вевая половина отсортирована, можно 
 * проверить условие left <= k <= mid. Если элемент k в левой 
 * отсортированной половине, то рекурсивно запустится обьычный бинарный 
 * поиск. Иначе - k в правой половине, но его местополодение неизвестно.
 * Так будет происходить деление, пока k не окажется в отсортированной 
 * половине.
 *
 * -- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --
 *
 *  Поиск корренктен, потому что всегда одна половина отсортирована и в ней
 * работает обычный бинарный поиск. Если искомого элемента k в ней нет, то
 * значит он в другой половине, половина которой отсортирована. Таким 
 * образом, когда-то K в любом случае попадет в отсортированную половину и 
 * найдется обычным бинарным поиском, даже если в этой половине будет всего 
 * 1 элемент.
 * Частный случай - когда массив сдвинут ровно на половину, тогда обе 
 * половину будут отсортированы. Но он не усложнит, а, наоборот, упростит 
 * задачу.
 *
 * -- ВРЕМЕННАЯ СЛОЖНОСТЬ --
 *
 *  В основе лежит обычный бинарный поиск - деление пополам. Поэтому 
 * временная сложность O(log n). Есть дополнительные проверки за O(1), но 
 * нет дополнительных итераций.
 *
 * -- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
 *
 *  O(n) для хранения одного массива из n элементов. И O(log n) для 
 * заполнения стека локальными переменными при рекурсии. 
 * Итого: O(n + log n).
 *
 *************************************************************************/

#include "solution.h"
#include <vector>
#include <cassert>

#include <iostream>

int search(const int& left, const int& right, const std::vector<int>& vec, 
           const int& k)
{
    int mid = (left + right) / 2;
    if (vec[mid] == k) return mid;
    if (left == right - 1) return -1;

    if (vec[left] <= vec[right - 1])
    {
        // Полуинтервал [left; right) отсортирован - обычный бинарный поиск

        if(vec[mid] > k) 
            return search(left, mid, vec, k);
        else
            return search(mid, right, vec, k);
    }   
    else
    {
        // Полуинтервал [left ; right) неотсортирован - проверка половин на 
        // отсортированность

        if (vec[left] <= vec[mid - 1])
        {
            // Левая половина [left ; mid) отсортирована

            if (vec[left] <= k && k <= vec[mid  - 1])
                return search(left, mid, vec, k);
            else
                return search(mid, right, vec, k);
        }
        else
        {
            // Левая половина [left ; mid) неотсортирована, значит правая 
            // половина [mid + 1 ; right) отсортирована

            if (vec[mid + 1] <= k && k <= vec[right - 1])
                return search(mid + 1, right, vec, k);
            else
                return search(left, mid, vec, k);
        }
    }
}

int broken_search(const std::vector<int>& vec, int k) 
{
    return search(0, vec.size(), vec, k);
}

void test() 
{
    std::vector<int> arr = {19, 21, 100, 101, 1, 4, 5, 7, 12};
    assert(6 == broken_search(arr, 5));
}