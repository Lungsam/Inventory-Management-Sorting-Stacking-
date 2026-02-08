//Find
PyObject* netRegisterErrorLog(PyObject* poSelf, PyObject* poArgs)
{
	...
}

///Add
#if defined(KD_MANAGE_INV)
PyObject* netSendInventoryManagement(PyObject* poSelf, PyObject* poArgs)
{
	BYTE subheader;
	if (!PyTuple_GetByte(poArgs, 0, &subheader))
		return Py_BuildException();

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	rkNetStream.SendInventoryManagement(subheader);

	return Py_BuildNone();
}
#endif

//Find
		{ "RegisterErrorLog",						netRegisterErrorLog,						METH_VARARGS },

///Add
#if defined(KD_MANAGE_INV)
		{ "SendInventoryManagement",				netSendInventoryManagement,					METH_VARARGS },
#endif