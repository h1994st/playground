#define pr_fmt(fmt) "%s: " fmt, KBUILD_MODNAME

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netdevice.h>
#include <linux/timer.h>
#include <linux/jiffies.h>

#ifndef NET_DEV_NAME
#error "Must provide NET_DEV_NAME!"
#endif

static struct timer_list net_monitor_timer;
static int timer_delay = 1000;

static struct net_device *net_dev;
static struct rtnl_link_stats64 stats;

static void net_monitor_cb(struct timer_list *timer) {
    int err;

    err = mod_timer(timer, jiffies + msecs_to_jiffies(timer_delay));
    if (err) {
        pr_err("Failed to set timer\n");
    }

    dev_get_stats(net_dev, &stats);
    pr_info("%s RX bytes: %llu\n", net_dev->name, stats.rx_bytes);
}

static int __init net_monitor_init(void) {
    int err;

    pr_info("Initializing network monitor module\n");
    pr_info("Process ID: %d\n", current->pid);
    pr_info("Process name: %s\n", current->comm);

    net_dev = dev_get_by_name(&init_net, NET_DEV_NAME);
    if (!net_dev) {
        pr_err("Failed to get network device\n");
        err = -EINVAL;
        goto failed;
    }

    timer_setup(&net_monitor_timer, net_monitor_cb, 0);
    err = mod_timer(&net_monitor_timer, jiffies + msecs_to_jiffies(timer_delay));
    if (err) {
        pr_err("Failed to set timer\n");
    } else {
        pr_info("Set timer: %d ms\n", timer_delay);
    }

    return 0;
failed:
    return err;
}

static void __exit net_monitor_exit(void) {
    pr_info("Exiting network monitor module\n");

    del_timer(&net_monitor_timer);
}

module_init(net_monitor_init);
module_exit(net_monitor_exit);

MODULE_AUTHOR("Shengtuo Hu");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.01");
