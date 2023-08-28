function translate_virtual_to_physical(virtualAddress):
    pageNum = extractPageNum(virtualAddress)
    offset = extractOffset(virtualAddress)
    
    if pageNum not in PageTable:
        raise PageFaultException
    
    physicalPageNumber = PageTable[pageNum]
    physicalAddress = combine(physicalPageNumber, offset)
    
    return physicalAddress