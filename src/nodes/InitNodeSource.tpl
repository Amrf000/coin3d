//$ TEMPLATE InitNodeSource(className)
  // Make sure we only initialize once.
  assert(So##className::classTypeId == SoType::badType());
  // Make sure superclass get initialized before subclass.
  assert(inherited::getClassTypeId() != SoType::badType());

  So##className::classTypeId =
    SoType::createType(inherited::getClassTypeId(), "##className",
                       &So##className::createInstance,
                       SoNode::nextActionMethodIndex++);
