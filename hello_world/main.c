#include <linux/module.h>

/* module initialiation point */
static int __init helloworld_init(void)
{
    pr_info("Hello World!\n");
    return 0;
}

/* module exit point */
static void __exit helloworld_exit(void)
{
    pr_info("Goodbyr World!\n");
}

/* register module init and exit points */
module_init(helloworld_init);
module_exit(helloworld_exit);

/* module license and other info */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Rajssss@GitHub.com");
MODULE_DESCRIPTION("Hello World kernel module");
MODULE_INFO(board, "Beaglebone Green");