/* $QNXLicenseC$ */

/*  Proto types for the fs_crypto library.
 */
struct migrate_status_s;
void fs_crypto_set_logging(
    FILE *logfile,
    const int verbosity);
int fs_crypto_domain_add(
    const char *path,
    int domain, 
    int type, 
    int state,
    int length, 
    const uint8_t bytes[],
    int *preply);
int fs_crypto_domain_remove(
    const char *path,
    int domain,
    int *preply);
int fs_crypto_domain_lock(
    const char *path,
    int domain,
    int *preply);
int fs_crypto_domain_unlock(
    const char *path,
    int domain, 
    int length, 
    const uint8_t bytes[],
    int *preply);
int fs_crypto_domain_query(
    const char *path,
    int domain,
    int *preply);
int fs_crypto_domain_key_size(void);
int fs_crypto_key_read(
    const char *path,
    int *plength,
    uint8_t bytes[],
    int *preply);
int fs_crypto_key_write(
    const char *path,
    int length, 
    const uint8_t bytes[],
    int *preply);
int fs_crypto_check(
    const char *path,
    int *preply);
int fs_crypto_enable(
    const char *path,
    int *preply);
int fs_crypto_enable_option(
    const char *path,
	uint32_t option,
	uint32_t domain,
    int *preply);
int fs_crypto_file_get_domain(
    const char *path,
    int *pdomain,
    int *preply);
int fs_crypto_file_set_domain(
    const char *path,
    int domain,
    int *preply);
int fs_crypto_file_move_domain(
    const char *path,
    int  domain,
    bool force,
    bool recurse,
    int *preply);
int fs_crypto_file_remove_domain(
    const char *path,
    bool force,
    bool recurse,
    int *preply);
int fs_crypto_key_gen(
    const char *password,
    int plen,
    const uint8_t *salt,
    int slen,
    uint8_t *key,
    int klen);
int fs_crypto_domain_key_change(
    const char *path,
    int domain, 
    int length, 
    const uint8_t org_key[],
    const uint8_t new_key[],
    int *preply);
int fs_crypto_domain_key_check(
    const char *path,
    int domain, 
    int length, 
    const uint8_t bytes[],
    int *preply);
int fs_crypto_migrate_tag(
    const char *path,
    int domain,
    int *preply);
int fs_crypto_migrate_state(
    const char *path,
    uint64_t *premaining,
    int *preply);
int fs_crypto_migrate_control(
    const char *path,
    uint32_t flags,
    uint64_t context,
    int *preply);
int fs_crypto_migrate_path(
    const char *path,
    int domain, 
    int *preply);
int fs_crypto_migrate_status(
    const char *path,
    struct migrate_status_s *status,
    int *preply);




#if defined(__QNXNTO__) && defined(__USESRCVERSION)
#include <sys/srcversion.h>
__SRCVERSION("$URL: http://svn/product/branches/6.6.0/trunk/lib/fscrypto/public/fs_crypto_api.h $ $Rev: 680886 $")
#endif
