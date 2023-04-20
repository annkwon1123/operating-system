#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/slab.h>

struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
};

static LIST_HEAD(birthday_list);

struct birthday *createBirthday(int day, int month, int year) {
	struct birthday newBirthday;
	newBirthday.day = day;
	newBirthday.month = month;
	newBirthday.year = year;
}

int simple_init(void) {
	printk("INSTALL MODULE: bdlist\n");
	return 0;
}

void sipmle_exit(void) {
}
