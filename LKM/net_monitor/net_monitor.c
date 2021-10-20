#define pr_fmt(fmt) "%s: " fmt, KBUILD_MODNAME

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netdevice.h>
#include <linux/timer.h>
#include <linux/jiffies.h>

#ifndef NET_DEV_NAME
#define NET_DEV_NAME "br0"
#endif

// 1000 ms
#define NET_MONITOR_DELAY 1000
static struct timer_list net_monitor_timer;

// store bytes received for every connected ports
#define NET_MONITOR_MAX_NUM 8
u64 dev_rx_bytes[NET_MONITOR_MAX_NUM] = {0x00};

static struct net_device *net_dev;

static void net_monitor_cb(struct timer_list *timer) {
    int err;
    int i = 0;
    struct net_device *br_port_dev;
    struct list_head *iter;
    struct rtnl_link_stats64 stats;
    u64 rx_bps;

    err = mod_timer(timer, jiffies + msecs_to_jiffies(NET_MONITOR_DELAY));
    if (err) {
        pr_err("Failed to set timer\n");
    }

    // retrieve traffic stats
    netdev_for_each_lower_dev(net_dev, br_port_dev, iter) {
        dev_get_stats(br_port_dev, &stats);

        rx_bps = (stats.rx_bytes - dev_rx_bytes[i]) * 8 * 1000 / NET_MONITOR_DELAY;
        pr_info("throughput (%s): %llu bps\n", br_port_dev->name, rx_bps);
        // TODO: if `rx_bps` is greater than the expected throughput, the
        //  authenticator will send a time-lock puzzle

        dev_rx_bytes[i++] = stats.rx_bytes;
    }
}

static int __init net_monitor_init(void) {
    int err;
    int i = 0;
    struct net_device *br_port_dev;
    struct list_head *iter;
    struct rtnl_link_stats64 stats;

    pr_info("Initializing network monitor module\n");

    net_dev = dev_get_by_name(&init_net, NET_DEV_NAME);
    if (!net_dev) {
        pr_err("Failed to get network device: %s\n", NET_DEV_NAME);
        err = -EINVAL;
        goto failed;
    }

    // initialize traffic stats
    netdev_for_each_lower_dev(net_dev, br_port_dev, iter) {
        dev_get_stats(br_port_dev, &stats);
        dev_rx_bytes[i++] = stats.rx_bytes;
        pr_info("Port (%s): %llu bytes\n", br_port_dev->name, stats.rx_bytes);
    }

    // initialize the timer
    timer_setup(&net_monitor_timer, net_monitor_cb, 0);
    err = mod_timer(
        &net_monitor_timer, jiffies + msecs_to_jiffies(NET_MONITOR_DELAY));
    if (err) {
        pr_err("Failed to set timer\n");
    } else {
        pr_info("Set timer: %d ms\n", NET_MONITOR_DELAY);
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
