//$ TEMPLATE ElementHeader(_classname_)
//$ INSERT TEMPLATE ElementClassTypeHeader()
public:
  static int getClassStackIndex(void);
  virtual ~_classname_(void);

  static void initClass(void);
  static void cleanClass(void);

protected:
  _classname_(void);
  static int classStackIndex;
