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

#ifndef UTILITIES_IDD_GROUNDHEATTRANSFER_BASEMENT_INTERIOR_FIELDENUMS_HXX
#define UTILITIES_IDD_GROUNDHEATTRANSFER_BASEMENT_INTERIOR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class GroundHeatTransfer_Basement_InteriorFields
 *  \brief Enumeration of GroundHeatTransfer:Basement:Interior's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(GroundHeatTransfer_Basement_InteriorFields, )
#else
class GroundHeatTransfer_Basement_InteriorFields: public ::EnumBase<GroundHeatTransfer_Basement_InteriorFields> {
 public: 
  enum domain 
  {
COND_Flag_Isthebasementconditioned, HIN_Downwardconvectiononlyheattransfercoefficient, HIN_Upwardconvectiononlyheattransfercoefficient, HIN_Horizontalconvectiononlyheattransfercoefficient, HIN_Downwardcombined_convectionandradiation_heattransfercoefficient, HIN_Upwardcombined_convectionandradiation_heattransfercoefficient, HIN_Horizontalcombined_convectionandradiation_heattransfercoefficient,   };
  GroundHeatTransfer_Basement_InteriorFields()
   : EnumBase<GroundHeatTransfer_Basement_InteriorFields>(COND_Flag_Isthebasementconditioned) {} 
  GroundHeatTransfer_Basement_InteriorFields(const std::string &t_name) 
   : EnumBase<GroundHeatTransfer_Basement_InteriorFields>(t_name) {} 
  GroundHeatTransfer_Basement_InteriorFields(int t_value) 
   : EnumBase<GroundHeatTransfer_Basement_InteriorFields>(t_value) {} 
  static std::string enumName() 
  { return "GroundHeatTransfer_Basement_InteriorFields"; }
  domain value() const { return static_cast<domain>(EnumBase<GroundHeatTransfer_Basement_InteriorFields>::value()); }
   private:
    friend class EnumBase<GroundHeatTransfer_Basement_InteriorFields>;
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
{ GroundHeatTransfer_Basement_InteriorFields::COND_Flag_Isthebasementconditioned, "COND_Flag_Isthebasementconditioned", "COND: Flag: Is the basement conditioned?"},
{ GroundHeatTransfer_Basement_InteriorFields::HIN_Downwardconvectiononlyheattransfercoefficient, "HIN_Downwardconvectiononlyheattransfercoefficient", "HIN: Downward convection only heat transfer coefficient"},
{ GroundHeatTransfer_Basement_InteriorFields::HIN_Upwardconvectiononlyheattransfercoefficient, "HIN_Upwardconvectiononlyheattransfercoefficient", "HIN: Upward convection only heat transfer coefficient"},
{ GroundHeatTransfer_Basement_InteriorFields::HIN_Horizontalconvectiononlyheattransfercoefficient, "HIN_Horizontalconvectiononlyheattransfercoefficient", "HIN: Horizontal convection only heat transfer coefficient"},
{ GroundHeatTransfer_Basement_InteriorFields::HIN_Downwardcombined_convectionandradiation_heattransfercoefficient, "HIN_Downwardcombined_convectionandradiation_heattransfercoefficient", "HIN: Downward combined (convection and radiation) heat transfer coefficient"},
{ GroundHeatTransfer_Basement_InteriorFields::HIN_Upwardcombined_convectionandradiation_heattransfercoefficient, "HIN_Upwardcombined_convectionandradiation_heattransfercoefficient", "HIN: Upward combined (convection and radiation) heat transfer coefficient"},
{ GroundHeatTransfer_Basement_InteriorFields::HIN_Horizontalcombined_convectionandradiation_heattransfercoefficient, "HIN_Horizontalcombined_convectionandradiation_heattransfercoefficient", "HIN: Horizontal combined (convection and radiation) heat transfer coefficient"},
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
  inline std::ostream &operator<<(std::ostream &os, const GroundHeatTransfer_Basement_InteriorFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<GroundHeatTransfer_Basement_InteriorFields> OptionalGroundHeatTransfer_Basement_InteriorFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GROUNDHEATTRANSFER_BASEMENT_INTERIOR_FIELDENUMS_HXX
