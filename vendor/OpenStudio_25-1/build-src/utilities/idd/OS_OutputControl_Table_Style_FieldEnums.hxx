/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_OUTPUTCONTROL_TABLE_STYLE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_OUTPUTCONTROL_TABLE_STYLE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_OutputControl_Table_StyleFields
 *  \brief Enumeration of OS:OutputControl:Table:Style's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_OutputControl_Table_StyleFields, )
#else
class OS_OutputControl_Table_StyleFields: public ::EnumBase<OS_OutputControl_Table_StyleFields> {
 public: 
  enum domain 
  {
Handle, ColumnSeparator, UnitConversion,   };
  OS_OutputControl_Table_StyleFields()
   : EnumBase<OS_OutputControl_Table_StyleFields>(Handle) {} 
  OS_OutputControl_Table_StyleFields(const std::string &t_name) 
   : EnumBase<OS_OutputControl_Table_StyleFields>(t_name) {} 
  OS_OutputControl_Table_StyleFields(int t_value) 
   : EnumBase<OS_OutputControl_Table_StyleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_OutputControl_Table_StyleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_OutputControl_Table_StyleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_OutputControl_Table_StyleFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ OS_OutputControl_Table_StyleFields::Handle, "Handle", "Handle"},
{ OS_OutputControl_Table_StyleFields::ColumnSeparator, "ColumnSeparator", "Column Separator"},
{ OS_OutputControl_Table_StyleFields::UnitConversion, "UnitConversion", "Unit Conversion"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const OS_OutputControl_Table_StyleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_OutputControl_Table_StyleFields> OptionalOS_OutputControl_Table_StyleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_OUTPUTCONTROL_TABLE_STYLE_FIELDENUMS_HXX
