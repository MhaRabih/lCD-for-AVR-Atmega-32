/*
 * utlis.h
 *
 *  Created on: Aug 9, 2019
 *      Author: maha_
 */

#ifndef UTLIS_H_
#define UTLIS_H_
#define Set_Bit(Var,BitNo) Var=Var|(1<<BitNo)
#define Clr_Bit(Var,BitNo) Var=(Var&(~(1<<BitNo)))
#define Get_Bit(Var,BitNo) (Var>>BitNo)&(0x01)
#define Toggle_Bit(Var,BitNo) Var=Var ^(1<<BitNo)
#define conc(x7,x6,x5,x4,x3,x2,x1,x0)  conchelper(x7,x6,x5,x4,x3,x2,x1,x0)
#define conchelper(x7,x6,x5,x4,x3,x2,x1,x0) 0b##x7##x6##x5##x4##x3##x2##x1##x0
#endif /* UTLIS_H_ */
