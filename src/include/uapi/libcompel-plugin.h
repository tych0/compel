#ifndef __UAPI_LIBCOMPEL_PLUGIN_H__
#define __UAPI_LIBCOMPEL_PLUGIN_H__

#define __init	__attribute__((__used__)) __attribute__ ((__section__(".compel.init")))
#define __exit	__attribute__((__used__)) __attribute__ ((__section__(".compel.exit")))

#ifndef __ASSEMBLY__

typedef struct {
	const char	*name;
	int		(*init)(int argc, char *argv[]);
	void		(*exit)(void);
} plugin_init_t;

#define plugin_register(___desc)				\
	static const plugin_init_t * const			\
	___ptr__##___desc __init = &___desc;

#define PLUGIN_REGISTER(___id, ___name, ___init, ___exit)	\
	static const plugin_init_t __plugin_desc_##___id = {	\
		.name = ___name,				\
		.init = ___init,				\
		.exit = ___exit,				\
	};							\
	plugin_register(__plugin_desc_##___id);

#define plugin_init_count(size)	((size) / (sizeof(plugin_init_t *)))

static inline int dummy_plugin_init(int argc, char *argv[]) { return 0; }
static inline void dummy_plugin_fini(void) { }

#define PLUGIN_REGISTER_DUMMY(___id)				\
	static const plugin_init_t __plugin_desc_##___id = {	\
		.name = #___id,					\
		.init = dummy_plugin_init,			\
		.exit = dummy_plugin_fini,			\
	};							\
	plugin_register(__plugin_desc_##___id);

#endif /* __ASSEMBLY__ */

#endif /* __UAPI_LIBCOMPEL_PLUGIN_H__ */
