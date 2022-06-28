#include <linux/module.h>   /* Needed by all modules */
#include <linux/kernel.h>   /* Needed for KERN_INFO */
#include <linux/gpio.h>     /* wird für Zugriff auf GPIO benötigt*/
#include <linux/kthread.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("SuperTrooper");
MODULE_DESCRIPTION("Blinky");
MODULE_VERSION("1.0");

#define LED_RED_PIN_BCM     21 /* wPi 29 */


struct task_struct *task;
static int nof = 5;
module_param(nof , int, S_IRUGO);
MODULE_PARM_DESC(nof , " BlinkFreqenz (default=5)");




static int thread(void *data){
int i;

	for(i = 0;i<nof; i++) {
		if (kthread_should_stop()) {
			break;
		}
		/* do something useful */
		gpio_set_value(LED_RED_PIN_BCM, 0);  
		msleep(100);
		gpio_set_value(LED_RED_PIN_BCM, 1);    
		msleep(1000);
	}  
	for(;;){
		if (kthread_should_stop()) {
			break;
		}
		msleep(1000);
	}
  return 0;
}


static int __init simple_init_module(void) {
  printk(KERN_INFO "MEP Kernel Modul geladen.\n");
  printk(KERN_INFO "Module loaded: blinky=%d\n", nof);
  /* A non-0 return means init_module failed; module can't be loaded.  */
  gpio_request(LED_RED_PIN_BCM, "LED_BLUE");
  gpio_direction_output(LED_RED_PIN_BCM, 0);
  gpio_set_value(LED_RED_PIN_BCM, 0);
  /* Task Stuff */	
  task = kthread_run(thread, NULL, "blinky");  
  return 0;
}

static void __exit simple_cleanup_module(void) {
  printk(KERN_INFO "Goodbye from a kernel module.\n");
  kthread_stop(task);  
  gpio_set_value(LED_RED_PIN_BCM, 0);  
  gpio_free(LED_RED_PIN_BCM);

}

module_init(simple_init_module);
module_exit(simple_cleanup_module);
