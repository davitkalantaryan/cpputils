# questions on c++  

Is it possible to distinguish which integer template argumet is bigger. 
To illustrate issue, let's have a look code below  
  
`` cpp  

template <int TemplSize>
class TemplClass{
	char buff[TemplSize];
};

// now the core question  

template <int TemplSize1,int TemplSize2>
void SomeFunction(const TemplClass<TemplSize1>& a_1,const TemplClass<TemplSize2>& a_2)
{
	// is it possible to know which template argument is bigger ?
}

``
