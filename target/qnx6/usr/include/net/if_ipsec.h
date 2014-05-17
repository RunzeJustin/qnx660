#ifdef __QNXNTO__
#ifndef IF_IPSEC_H_
#define IF_IPSEC_H_
#include <net/if.h>
/* Configuration structure for SIOCSETIFIPSEC and SIOCGETIFIPSEC ioctls. */
struct ifipsecreq {
	char		ipsecr_parent[IFNAMSIZ];
	unsigned short	ipsecr_tag;
};

#define	SIOCSETIFIPSEC	SIOCSIFGENERIC
#define	SIOCGETIFIPSEC	SIOCGIFGENERIC

#ifdef _KERNEL
void	ipsec_input(struct ifnet *, struct mbuf *);
#endif	/* _KERNEL */

#endif /* IF_IPSEC_H_ */
#endif

#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/socket/public/net/if_ipsec.h $ $Rev: 680336 $")
#endif
