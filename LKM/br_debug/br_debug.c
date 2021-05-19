#define pr_fmt(fmt) "%s: " fmt, KBUILD_MODNAME

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_bridge.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/kallsyms.h>

#if !IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
#warning "BRIDGE_NETFILTER is disabled!"
#endif

#if IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
static unsigned int br_pre_routing_first_hookfn(void *priv,
                                                struct sk_buff *skb,
                                                const struct nf_hook_state *state)
{
    const struct nf_hook_entry *hook;
    struct nf_hook_entries *hooks = NULL;
    struct net *net;
    int i;

    pr_info("NF_BR_PRE_ROUTING first\n");
    pr_info("skb=%px: len=%u headroom=%u head=%px data=%px, tail=%u, end=%u\n",
            skb, skb->len, skb_headroom(skb), skb->head, skb->data, skb->tail, skb->end);

    net = dev_net(skb->dev);
    hooks = rcu_dereference(net->nf.hooks_bridge[NF_BR_PRE_ROUTING]);
    if (!hooks)
        goto out;

    pr_info("#hooks of NF_BR_PRE_ROUTING: %u\n", hooks->num_hook_entries);
    for (i = 0; i < hooks->num_hook_entries; ++i) {
        hook = &hooks->hooks[i];
        pr_info("hook %d: %pF\n", i, hook->hook);
    }

out:
    return NF_ACCEPT;
}

static unsigned int br_pre_routing_last_hookfn(void *priv,
                                               struct sk_buff *skb,
                                               const struct nf_hook_state *state)
{
    pr_info("NF_BR_PRE_ROUTING last\n");
    pr_info("skb=%px: len=%u headroom=%u head=%px data=%px, tail=%u, end=%u\n",
            skb, skb->len, skb_headroom(skb), skb->head, skb->data, skb->tail, skb->end);

    return NF_ACCEPT;
}

static unsigned int inet_pre_routing_first_hookfn(void *priv,
                                                  struct sk_buff *skb,
                                                  const struct nf_hook_state *state)
{
    const struct nf_hook_entry *hook;
    struct nf_hook_entries *hooks = NULL;
    struct net *net;
    int i;

    pr_info("NF_INET_PRE_ROUTING first\n");
    pr_info("skb=%px: len=%u headroom=%u head=%px data=%px, tail=%u, end=%u\n",
            skb, skb->len, skb_headroom(skb), skb->head, skb->data, skb->tail, skb->end);

    net = dev_net(skb->dev);
    hooks = rcu_dereference(net->nf.hooks_ipv4[NF_INET_PRE_ROUTING]);
    if (!hooks)
        goto out;

    pr_info("#hooks of NF_INET_PRE_ROUTING: %u\n", hooks->num_hook_entries);
    for (i = 0; i < hooks->num_hook_entries; ++i) {
        hook = &hooks->hooks[i];
        pr_info("hook %d: %pF\n", i, hook->hook);
    }

out:
    return NF_ACCEPT;
}

static unsigned int inet_pre_routing_last_hookfn(void *priv,
                                                 struct sk_buff *skb,
                                                 const struct nf_hook_state *state)
{
    pr_info("NF_INET_PRE_ROUTING last\n");
    pr_info("skb=%px: len=%u headroom=%u head=%px data=%px, tail=%u, end=%u\n",
            skb, skb->len, skb_headroom(skb), skb->head, skb->data, skb->tail, skb->end);

    return NF_ACCEPT;
}

static unsigned int br_local_in_hookfn(void *priv,
                                       struct sk_buff *skb,
                                       const struct nf_hook_state *state)
{
    pr_info("NF_BR_LOCAL_IN\n");
    pr_info("skb=%px: len=%u headroom=%u head=%px data=%px, tail=%u, end=%u\n",
            skb, skb->len, skb_headroom(skb), skb->head, skb->data, skb->tail, skb->end);
    return NF_ACCEPT;
}

static unsigned int br_forward_hookfn(void *priv,
                                      struct sk_buff *skb,
                                      const struct nf_hook_state *state)
{
    pr_info("NF_BR_FORWARD\n");
    pr_info("skb=%px: len=%u headroom=%u head=%px data=%px, tail=%u, end=%u\n",
            skb, skb->len, skb_headroom(skb), skb->head, skb->data, skb->tail, skb->end);
    return NF_ACCEPT;
}

static unsigned int br_local_out_hookfn(void *priv,
                                        struct sk_buff *skb,
                                        const struct nf_hook_state *state)
{
    pr_info("NF_BR_LOCAL_OUT\n");
    pr_info("skb=%px: len=%u headroom=%u head=%px data=%px, tail=%u, end=%u\n",
            skb, skb->len, skb_headroom(skb), skb->head, skb->data, skb->tail, skb->end);
    return NF_ACCEPT;
}

static unsigned int br_post_routing_hookfn(void *priv,
                                           struct sk_buff *skb,
                                           const struct nf_hook_state *state)
{
    pr_info("NF_BR_POST_ROUTING\n");
    pr_info("skb=%px: len=%u headroom=%u head=%px data=%px, tail=%u, end=%u\n",
            skb, skb->len, skb_headroom(skb), skb->head, skb->data, skb->tail, skb->end);
    return NF_ACCEPT;
}
#endif

static const struct nf_hook_ops br_debug_nf_ops[] = {
#if IS_ENABLED(CONFIG_BRIDGE_NETFILTER)
    {
        .hook = br_pre_routing_first_hookfn,
        .pf = NFPROTO_BRIDGE,
        .hooknum = NF_BR_PRE_ROUTING,
        .priority = NF_BR_PRI_FIRST,
    },
    {
        .hook = br_pre_routing_last_hookfn,
        .pf = NFPROTO_BRIDGE,
        .hooknum = NF_BR_PRE_ROUTING,
        .priority = NF_BR_PRI_LAST,
    },
    {
        .hook = inet_pre_routing_first_hookfn,
        .pf = NFPROTO_IPV4,
        .hooknum = NF_INET_PRE_ROUTING,
        .priority = NF_BR_PRI_FIRST,
    },
    {
        .hook = inet_pre_routing_last_hookfn,
        .pf = NFPROTO_IPV4,
        .hooknum = NF_INET_PRE_ROUTING,
        .priority = NF_BR_PRI_LAST,
    },
    {
        .hook = br_local_in_hookfn,
        .pf = NFPROTO_BRIDGE,
        .hooknum = NF_BR_LOCAL_IN,
        .priority = NF_BR_PRI_FIRST,
    },
    {
        .hook = br_forward_hookfn,
        .pf = NFPROTO_BRIDGE,
        .hooknum = NF_BR_FORWARD,
        .priority = NF_BR_PRI_FIRST,
    },
    {
        .hook = br_local_out_hookfn,
        .pf = NFPROTO_BRIDGE,
        .hooknum = NF_BR_LOCAL_OUT,
        .priority = NF_BR_PRI_FIRST,
    },
    {
        .hook = br_post_routing_hookfn,
        .pf = NFPROTO_BRIDGE,
        .hooknum = NF_BR_POST_ROUTING,
        .priority = NF_BR_PRI_FIRST,
    },
#endif
};

static int __net_init br_debug_nf_register(struct net *net)
{
    if (net_eq(net, &init_net)) {
        // do not hook the root network namespace
        return 0;
    }

    return nf_register_net_hooks(net, br_debug_nf_ops,
                                 ARRAY_SIZE(br_debug_nf_ops));
}

static void __net_exit br_debug_nf_unregister(struct net *net)
{
    if (net_eq(net, &init_net)) {
        // no hook for the root network namespace
        return;
    }
    nf_unregister_net_hooks(net, br_debug_nf_ops,
                            ARRAY_SIZE(br_debug_nf_ops));
}

static struct pernet_operations br_debug_net_ops = {
    .init = br_debug_nf_register,
    .exit = br_debug_nf_unregister,
};

static int __init br_debug_init(void)
{
    int err;

    pr_debug("Bridge debug: registering netfilter hooks\n");

    err = register_pernet_subsys(&br_debug_net_ops);
    if (err)
        return err;

    return 0;
}

static void __exit br_debug_exit(void)
{
    pr_debug("Bridge debug: unregistering netfilter hooks\n");

    unregister_pernet_subsys(&br_debug_net_ops);
}

module_init(br_debug_init);
module_exit(br_debug_exit);

MODULE_AUTHOR("Shengtuo Hu");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.01");
