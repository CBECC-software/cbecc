/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_TABLE_INDEPENDENTVARIABLE_FIELDENUMS_HXX
#define UTILITIES_IDD_TABLE_INDEPENDENTVARIABLE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Table_IndependentVariableFields
 *  \brief Enumeration of Table:IndependentVariable's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Table_IndependentVariableFields, )
#else
class Table_IndependentVariableFields: public ::EnumBase<Table_IndependentVariableFields> {
 public: 
  enum domain 
  {
Name, InterpolationMethod, ExtrapolationMethod, MinimumValue, MaximumValue, NormalizationReferenceValue, UnitType, ExternalFileName, ExternalFileColumnNumber, ExternalFileStartingRowNumber,   };
  Table_IndependentVariableFields()
   : EnumBase<Table_IndependentVariableFields>(Name) {} 
  Table_IndependentVariableFields(const std::string &t_name) 
   : EnumBase<Table_IndependentVariableFields>(t_name) {} 
  Table_IndependentVariableFields(int t_value) 
   : EnumBase<Table_IndependentVariableFields>(t_value) {} 
  static std::string enumName() 
  { return "Table_IndependentVariableFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Table_IndependentVariableFields>::integer_value()); }
   private:
    friend class EnumBase<Table_IndependentVariableFields>;
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
{ Table_IndependentVariableFields::Name, "Name", "Name"},
{ Table_IndependentVariableFields::InterpolationMethod, "InterpolationMethod", "Interpolation Method"},
{ Table_IndependentVariableFields::ExtrapolationMethod, "ExtrapolationMethod", "Extrapolation Method"},
{ Table_IndependentVariableFields::MinimumValue, "MinimumValue", "Minimum Value"},
{ Table_IndependentVariableFields::MaximumValue, "MaximumValue", "Maximum Value"},
{ Table_IndependentVariableFields::NormalizationReferenceValue, "NormalizationReferenceValue", "Normalization Reference Value"},
{ Table_IndependentVariableFields::UnitType, "UnitType", "Unit Type"},
{ Table_IndependentVariableFields::ExternalFileName, "ExternalFileName", "External File Name"},
{ Table_IndependentVariableFields::ExternalFileColumnNumber, "ExternalFileColumnNumber", "External File Column Number"},
{ Table_IndependentVariableFields::ExternalFileStartingRowNumber, "ExternalFileStartingRowNumber", "External File Starting Row Number"},
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
  inline std::ostream &operator<<(std::ostream &os, const Table_IndependentVariableFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Table_IndependentVariableFields> OptionalTable_IndependentVariableFields ;
#endif

/** \class Table_IndependentVariableExtensibleFields
 *  \brief Enumeration of Table:IndependentVariable's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Table_IndependentVariableExtensibleFields, )
#else
class Table_IndependentVariableExtensibleFields: public ::EnumBase<Table_IndependentVariableExtensibleFields> {
 public: 
  enum domain 
  {
Value,   };
  Table_IndependentVariableExtensibleFields()
   : EnumBase<Table_IndependentVariableExtensibleFields>(Value) {} 
  Table_IndependentVariableExtensibleFields(const std::string &t_name) 
   : EnumBase<Table_IndependentVariableExtensibleFields>(t_name) {} 
  Table_IndependentVariableExtensibleFields(int t_value) 
   : EnumBase<Table_IndependentVariableExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Table_IndependentVariableExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Table_IndependentVariableExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<Table_IndependentVariableExtensibleFields>;
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
{ Table_IndependentVariableExtensibleFields::Value, "Value", "Value"},
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
  inline std::ostream &operator<<(std::ostream &os, const Table_IndependentVariableExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Table_IndependentVariableExtensibleFields> OptionalTable_IndependentVariableExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_TABLE_INDEPENDENTVARIABLE_FIELDENUMS_HXX
