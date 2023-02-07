#ifndef MENU_H
#define MENU_H

/**
 * Available actions:
 * 
 * Show the menu: run().
 * @brief Represents menu with desired items assigned by initializer list.
 */
class Menu {
private:
	const char ** m_items; /* The menu items. */
	int m_itemCnt; /* Count of menu items. */
	void selectItem(int itemNum) const; /* Prints selection of item with number itemNum. */
	int itemCnt() const; /* Returns number of items in the menu. */
public:
	/**
	 * Initializes the menu with items from initializer list.
	 * @param list The initializer list with names of menu items.
	 */
	Menu(std::initializer_list<const char *> list);
	
	~Menu();
	
	/**
	 * Shows the menu and allows the user to choose an item.
	 * @return Index of menu item chosen by the user.
	 */
	int run() const;
};


#endif /* MENU_H */