/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
*  All rights reserved.
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#ifndef UTILITIES_IDD_TABLE_TWOINDEPENDENTVARIABLES_FIELDENUMS_HXX
#define UTILITIES_IDD_TABLE_TWOINDEPENDENTVARIABLES_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Table_TwoIndependentVariablesFields
 *  \brief Enumeration of Table:TwoIndependentVariables's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Table_TwoIndependentVariablesFields, )
#else
class Table_TwoIndependentVariablesFields: public ::EnumBase<Table_TwoIndependentVariablesFields> {
 public: 
  enum domain 
  {
Name, CurveType, InterpolationMethod, MinimumValueofX, MaximumValueofX, MinimumValueofY, MaximumValueofY, MinimumTableOutput, MaximumTableOutput, InputUnitTypeforX, InputUnitTypeforY, OutputUnitType, NormalizationReference,   };
  Table_TwoIndependentVariablesFields()
   : EnumBase<Table_TwoIndependentVariablesFields>(Name) {} 
  Table_TwoIndependentVariablesFields(const std::string &t_name) 
   : EnumBase<Table_TwoIndependentVariablesFields>(t_name) {} 
  Table_TwoIndependentVariablesFields(int t_value) 
   : EnumBase<Table_TwoIndependentVariablesFields>(t_value) {} 
  static std::string enumName() 
  { return "Table_TwoIndependentVariablesFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Table_TwoIndependentVariablesFields>::value()); }
   private:
    friend class EnumBase<Table_TwoIndependentVariablesFields>;
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
{ Table_TwoIndependentVariablesFields::Name, "Name", "Name"},
{ Table_TwoIndependentVariablesFields::CurveType, "CurveType", "Curve Type"},
{ Table_TwoIndependentVariablesFields::InterpolationMethod, "InterpolationMethod", "Interpolation Method"},
{ Table_TwoIndependentVariablesFields::MinimumValueofX, "MinimumValueofX", "Minimum Value of X"},
{ Table_TwoIndependentVariablesFields::MaximumValueofX, "MaximumValueofX", "Maximum Value of X"},
{ Table_TwoIndependentVariablesFields::MinimumValueofY, "MinimumValueofY", "Minimum Value of Y"},
{ Table_TwoIndependentVariablesFields::MaximumValueofY, "MaximumValueofY", "Maximum Value of Y"},
{ Table_TwoIndependentVariablesFields::MinimumTableOutput, "MinimumTableOutput", "Minimum Table Output"},
{ Table_TwoIndependentVariablesFields::MaximumTableOutput, "MaximumTableOutput", "Maximum Table Output"},
{ Table_TwoIndependentVariablesFields::InputUnitTypeforX, "InputUnitTypeforX", "Input Unit Type for X"},
{ Table_TwoIndependentVariablesFields::InputUnitTypeforY, "InputUnitTypeforY", "Input Unit Type for Y"},
{ Table_TwoIndependentVariablesFields::OutputUnitType, "OutputUnitType", "Output Unit Type"},
{ Table_TwoIndependentVariablesFields::NormalizationReference, "NormalizationReference", "Normalization Reference"},
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
  inline std::ostream &operator<<(std::ostream &os, const Table_TwoIndependentVariablesFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Table_TwoIndependentVariablesFields> OptionalTable_TwoIndependentVariablesFields ;
#endif

/** \class Table_TwoIndependentVariablesExtensibleFields
 *  \brief Enumeration of Table:TwoIndependentVariables's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Table_TwoIndependentVariablesExtensibleFields, )
#else
class Table_TwoIndependentVariablesExtensibleFields: public ::EnumBase<Table_TwoIndependentVariablesExtensibleFields> {
 public: 
  enum domain 
  {
XValue, YValue, OutputValue,   };
  Table_TwoIndependentVariablesExtensibleFields()
   : EnumBase<Table_TwoIndependentVariablesExtensibleFields>(XValue) {} 
  Table_TwoIndependentVariablesExtensibleFields(const std::string &t_name) 
   : EnumBase<Table_TwoIndependentVariablesExtensibleFields>(t_name) {} 
  Table_TwoIndependentVariablesExtensibleFields(int t_value) 
   : EnumBase<Table_TwoIndependentVariablesExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Table_TwoIndependentVariablesExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Table_TwoIndependentVariablesExtensibleFields>::value()); }
   private:
    friend class EnumBase<Table_TwoIndependentVariablesExtensibleFields>;
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
{ Table_TwoIndependentVariablesExtensibleFields::XValue, "XValue", "X Value"},
{ Table_TwoIndependentVariablesExtensibleFields::YValue, "YValue", "Y Value"},
{ Table_TwoIndependentVariablesExtensibleFields::OutputValue, "OutputValue", "Output Value"},
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
  inline std::ostream &operator<<(std::ostream &os, const Table_TwoIndependentVariablesExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Table_TwoIndependentVariablesExtensibleFields> OptionalTable_TwoIndependentVariablesExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_TABLE_TWOINDEPENDENTVARIABLES_FIELDENUMS_HXX
