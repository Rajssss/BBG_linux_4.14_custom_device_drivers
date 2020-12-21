#include <linux/module.h>

/* module initialization entry point */
static int __init helloworld_init(void)
{
	pr_info("Hello Linux World!\n");
	return 0;
}

/* module clean-up entry point */
static void __exit helloworld_cleanup(void)
{
	pr_info("Good Bye Linux World!\n");
}

/* register the entry points of the module */
module_init(helloworld_init);
module_exit(helloworld_cleanup);

/* Module License and Description  */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rajssss@GitHub.com");
MODULE_DESCRIPTION("Hello World kernel Module.");
MODULE_INFO(board, "Beaglebone Green.");

