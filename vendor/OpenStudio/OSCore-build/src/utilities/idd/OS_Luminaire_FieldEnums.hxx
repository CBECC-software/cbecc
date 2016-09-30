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

#ifndef UTILITIES_IDD_OS_LUMINAIRE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_LUMINAIRE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_LuminaireFields
 *  \brief Enumeration of OS:Luminaire's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_LuminaireFields, )
#else
class OS_LuminaireFields: public ::EnumBase<OS_LuminaireFields> {
 public: 
  enum domain 
  {
Handle, Name, LuminaireDefinitionName, SpaceorSpaceTypeName, ScheduleName, PositionXcoordinate, PositionYcoordinate, PositionZcoordinate, PsiRotationAroundXaxis, ThetaRotationAroundYaxis, PhiRotationAroundZaxis, FractionReplaceable, Multiplier, EndUseSubcategory,   };
  OS_LuminaireFields()
   : EnumBase<OS_LuminaireFields>(Handle) {} 
  OS_LuminaireFields(const std::string &t_name) 
   : EnumBase<OS_LuminaireFields>(t_name) {} 
  OS_LuminaireFields(int t_value) 
   : EnumBase<OS_LuminaireFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_LuminaireFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_LuminaireFields>::value()); }
   private:
    friend class EnumBase<OS_LuminaireFields>;
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
{ OS_LuminaireFields::Handle, "Handle", "Handle"},
{ OS_LuminaireFields::Name, "Name", "Name"},
{ OS_LuminaireFields::LuminaireDefinitionName, "LuminaireDefinitionName", "Luminaire Definition Name"},
{ OS_LuminaireFields::SpaceorSpaceTypeName, "SpaceorSpaceTypeName", "Space or SpaceType Name"},
{ OS_LuminaireFields::ScheduleName, "ScheduleName", "Schedule Name"},
{ OS_LuminaireFields::PositionXcoordinate, "PositionXcoordinate", "Position X-coordinate"},
{ OS_LuminaireFields::PositionYcoordinate, "PositionYcoordinate", "Position Y-coordinate"},
{ OS_LuminaireFields::PositionZcoordinate, "PositionZcoordinate", "Position Z-coordinate"},
{ OS_LuminaireFields::PsiRotationAroundXaxis, "PsiRotationAroundXaxis", "Psi Rotation Around X-axis"},
{ OS_LuminaireFields::ThetaRotationAroundYaxis, "ThetaRotationAroundYaxis", "Theta Rotation Around Y-axis"},
{ OS_LuminaireFields::PhiRotationAroundZaxis, "PhiRotationAroundZaxis", "Phi Rotation Around Z-axis"},
{ OS_LuminaireFields::FractionReplaceable, "FractionReplaceable", "Fraction Replaceable"},
{ OS_LuminaireFields::Multiplier, "Multiplier", "Multiplier"},
{ OS_LuminaireFields::EndUseSubcategory, "EndUseSubcategory", "End-Use Subcategory"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_LuminaireFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_LuminaireFields> OptionalOS_LuminaireFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_LUMINAIRE_FIELDENUMS_HXX
