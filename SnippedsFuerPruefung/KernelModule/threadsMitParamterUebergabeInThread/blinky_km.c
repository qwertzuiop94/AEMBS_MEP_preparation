#include <linux/module.h>   /* Needed by all modules */
#include <linux/kernel.h>   /* Needed for KERN_INFO */
#include <linux/gpio.h>     /* interface to GPIO */
#include <linux/kobject.h>  /* IRQ interface */
#include <linux/kthread.h>  /* kernel threading */
#include <linux/delay.h>    /* waiting and delay */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Manuel Roos"); /* \todo Use your name */
MODULE_DESCRIPTION("Blinky Kernel Module");
MODULE_VERSION("0.0"); /* \todo increment version */

/* \todo Use blue LED for blinky */
#define LED_BLUE_PIN_BCM    12 /* wPi 26 */

/* \todo Define kernel module parameter for the number of blinks, with a default of 5 */
static int data = 5;
module_param(data, int, S_IRUGO);
MODULE_PARM_DESC(data, " Anzahl Blinks (default=5)");


static int blinkyThread(void *data) {
uint i = *((uint *)data);
uint j = 2;
printk(KERN_INFO "j inschleife=%d\n", j);
printk(KERN_INFO "i inschleife=%d\n", i);
for(;;){
msleep(250);
}
/*
for(i = 0; i<=j; i++){


gpio_set_value(LED_BLUE_PIN_BCM, 0);  
msleep(250);
gpio_set_value(LED_BLUE_PIN_BCM, 1);    
msleep(250);

}
*/

  return 0; /* ok */
}

static int __init blinky_init_module(void) {
  printk(KERN_INFO "Init blinky kernel module.\n");
  /* \todo Write number of blinks to kernel log */
  printk(KERN_INFO "Module loaded: Anzahl Blinks=%d\n", data);
  gpio_request(LED_BLUE_PIN_BCM, "LED");
  gpio_direction_output(LED_BLUE_PIN_BCM, 0); /* default low */
  kthread_run(blinkyThread, &data, "led_thread");  /* \todo pass number of blinks to thread */
  return 0; /* non-zero means failed, module cannot be loaded */
}

static void __exit blinky_cleanup_module(void) {
  printk(KERN_INFO "Cleanup blinky kernel module.\n");
  gpio_set_value(LED_BLUE_PIN_BCM, 0); /* off */
  gpio_free(LED_BLUE_PIN_BCM);
}

module_init(blinky_init_module);
module_exit(blinky_cleanup_module);
