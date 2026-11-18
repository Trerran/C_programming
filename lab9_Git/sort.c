void bubble_sort(int size, int arr[size]) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) { // текущий больше следующего, меняем местами
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}
//Это одна из самых простых сортировок
//В среднем и худшем случаях сложность алгоритма составляет O(n²)
