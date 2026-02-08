///Add
#if defined(KD_MANAGE_INV)
	PyModule_AddIntConstant(poModule, "KD_MANAGE_INV", true);
#else
	PyModule_AddIntConstant(poModule, "KD_MANAGE_INV", false);
#endif