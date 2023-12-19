#include <stdio.h>
#include <string.h>

void *bsearch(const void *key, const void *base, size_t num, size_t size, int (*compar)(const void *, const void *))
{
    size_t left_element = 0;
    size_t right_element = num - 1;

    while (left_element <= right_element)
    {
        size_t mid_element = left_element + (right_element - left_element) / 2;
        void *mid_ptr = (void *)((char *)base + (mid_element * size));
        int cmp = compar(key, mid_ptr);

        if (cmp == 0)
        {
            return mid_ptr;
        }
        else if (cmp < 0)
        {
            right_element = mid_element - 1;
        }
        else
        {
            left_element = mid_element + 1;
        }
    }

    return NULL;
}

int cmp(const void *key_element, const void *current_array_member)
{
    const void *key = key_element;
    const void *element_to_compare = current_array_member;

    if (*(int *)key < *(int *)element_to_compare)
        return -1;
    else if (*(int *)key > *(int *)element_to_compare)
        return 1;
    else
        return 0;
}

int cmp_string(const void *key_element, const void *current_array_member)
{
    const char *key = *(const char **)key_element;
    const char *element_to_compare = *(const char **)current_array_member;

    return strcmp(key, element_to_compare);
}

int main()
{
    int key_int;
    printf("Enter the integer key: ");
    scanf("%d", &key_int);

    int array_int[] = {10, 20, 30, 40, 50};
    int size_int = sizeof(array_int) / sizeof(array_int[0]);

    int *result_int = (int *)bsearch(&key_int, array_int, size_int, sizeof(int), cmp);

    if (result_int != NULL)
        printf("Integer key found at index %ld\n", result_int - array_int);
    else
        printf("Integer key not found\n");

    float key_float;
    printf("Enter the float key: ");
    scanf("%f", &key_float);

    float array_float[] = {10.5, 20.5, 30.5, 40.5, 50.5};
    int size_float = sizeof(array_float) / sizeof(array_float[0]);

    float *result_float = (float *)bsearch(&key_float, array_float, size_float, sizeof(float), cmp);

    if (result_float != NULL)
        printf("Float key found at index %ld\n", result_float - array_float);
    else
        printf("Float key not found\n");

    const char *array_string[] = {"Lucas", "Peter", "Wojtek"};

    const char *key_string = "Peter";

    int size_string = sizeof(array_string) / sizeof(array_string[0]);

    const char **result_string = bsearch(&key_string, array_string, size_string, sizeof(const char*), cmp_string);

    if (result_string != NULL)
        printf("\nString key found at index %ld\n", result_string - array_string);
    else
        printf("String key not found\n");
    return 0;
}
