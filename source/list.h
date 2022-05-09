enum state {
    LIR,
    Resident_HIR,
    Non_resident_HIR
};

struct element {
    int name;
    enum state state_element;
    void *location_in_cache;
};

struct dlinked_list_element {
    struct element element;
    struct dlinked_list_element *next;
    struct dlinked_list_element *previous;
};

void new_in_list(int name, void *location_in_cash, struct dlinked_list_element **upper_in_list, struct dlinked_list_element **down_in_list, struct element_hash **hash);
struct dlinked_list_element *create_elem(int name, void *location_in_cache);
void delete_element(struct dlinked_list_element **det_elem, struct element_hash **hash);

struct element add_in_list(int name, struct dlinked_list_element **upper_in_list, struct dlinked_list_element **down_in_list, struct element_hash **hash); //return struct delete element
//Добавление пришедшего элемента сверху, удаление нижнего, возвращение копии удаленной структуры

struct element move_up_list(int name, struct dlinked_list_element **upper_in_list, struct element_hash **hash); // return move element
////Перемещение указанного элемента наверх, возврат копии его структуры

void change_in_list(struct element add, int name_delite, struct dlinked_list_element **upper_in_list, struct element_hash **hash);
///Добавление add сверху, удаление элемента name_delite из списка(поиск его аддреса через хеш) это же когда удаляемый элемент попадает в LIR?
