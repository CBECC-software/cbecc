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

#ifndef UTILITIES_IDD_TABLE_ONEINDEPENDENTVARIABLE_FIELDENUMS_HXX
#define UTILITIES_IDD_TABLE_ONEINDEPENDENTVARIABLE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Table_OneIndependentVariableFields
 *  \brief Enumeration of Table:OneIndependentVariable's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Table_OneIndependentVariableFields, )
#else
class Table_OneIndependentVariableFields: public ::EnumBase<Table_OneIndependentVariableFields> {
 public: 
  enum domain 
  {
Name, CurveType, InterpolationMethod, MinimumValueofX, MaximumValueofX, MinimumTableOutput, MaximumTableOutput, InputUnitTypeforX, OutputUnitType, NormalizationReference,   };
  Table_OneIndependentVariableFields()
   : EnumBase<Table_OneIndependentVariableFields>(Name) {} 
  Table_OneIndependentVariableFields(const std::string &t_name) 
   : EnumBase<Table_OneIndependentVariableFields>(t_name) {} 
  Table_OneIndependentVariableFields(int t_value) 
   : EnumBase<Table_OneIndependentVariableFields>(t_value) {} 
  static std::string enumName() 
  { return "Table_OneIndependentVariableFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Table_OneIndependentVariableFields>::value()); }
   private:
    friend class EnumBase<Table_OneIndependentVariableFields>;
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
{ Table_OneIndependentVariableFields::Name, "Name", "Name"},
{ Table_OneIndependentVariableFields::CurveType, "CurveType", "Curve Type"},
{ Table_OneIndependentVariableFields::InterpolationMethod, "InterpolationMethod", "Interpolation Method"},
{ Table_OneIndependentVariableFields::MinimumValueofX, "MinimumValueofX", "Minimum Value of X"},
{ Table_OneIndependentVariableFields::MaximumValueofX, "MaximumValueofX", "Maximum Value of X"},
{ Table_OneIndependentVariableFields::MinimumTableOutput, "MinimumTableOutput", "Minimum Table Output"},
{ Table_OneIndependentVariableFields::MaximumTableOutput, "MaximumTableOutput", "Maximum Table Output"},
{ Table_OneIndependentVariableFields::InputUnitTypeforX, "InputUnitTypeforX", "Input Unit Type for X"},
{ Table_OneIndependentVariableFields::OutputUnitType, "OutputUnitType", "Output Unit Type"},
{ Table_OneIndependentVariableFields::NormalizationReference, "NormalizationReference", "Normalization Reference"},
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
  inline std::ostream &operator<<(std::ostream &os, const Table_OneIndependentVariableFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Table_OneIndependentVariableFields> OptionalTable_OneIndependentVariableFields ;
#endif

/** \class Table_OneIndependentVariableExtensibleFields
 *  \brief Enumeration of Table:OneIndependentVariable's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Table_OneIndependentVariableExtensibleFields, )
#else
class Table_OneIndependentVariableExtensibleFields: public ::EnumBase<Table_OneIndependentVariableExtensibleFields> {
 public: 
  enum domain 
  {
XValue, OutputValue,   };
  Table_OneIndependentVariableExtensibleFields()
   : EnumBase<Table_OneIndependentVariableExtensibleFields>(XValue) {} 
  Table_OneIndependentVariableExtensibleFields(const std::string &t_name) 
   : EnumBase<Table_OneIndependentVariableExtensibleFields>(t_name) {} 
  Table_OneIndependentVariableExtensibleFields(int t_value) 
   : EnumBase<Table_OneIndependentVariableExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Table_OneIndependentVariableExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Table_OneIndependentVariableExtensibleFields>::value()); }
   private:
    friend class EnumBase<Table_OneIndependentVariableExtensibleFields>;
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
{ Table_OneIndependentVariableExtensibleFields::XValue, "XValue", "X Value"},
{ Table_OneIndependentVariableExtensibleFields::OutputValue, "OutputValue", "Output Value"},
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
  inline std::ostream &operator<<(std::ostream &os, const Table_OneIndependentVariableExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Table_OneIndependentVariableExtensibleFields> OptionalTable_OneIndependentVariableExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_TABLE_ONEINDEPENDENTVARIABLE_FIELDENUMS_HXX
