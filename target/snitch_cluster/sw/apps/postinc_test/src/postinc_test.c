#include <snrt.h>

#include "printf.h"

int main() {
 uint32_t i = snrt_global_core_idx(); 
         snrt_cluster_hw_barrier();
	 if (i == 2) {
    int errs = 0;
	int32_t result_rd;
        int32_t result_rs1;
	int8_t *mem8 = (int8_t *)0x10000000;
	mem8[0] = 0x21;
	 register int32_t rd asm("a3") = 1;   
         register int32_t rs1 asm("a4") = 0x10000000; // rs1, data source
        // P_LB_IRPOST
        asm volatile(                         //incr +4 to rs1
            ".word (0b000000000100 << 20) | \
             (     (14) << 15) | \
             (    0b000 << 12) | \
             (    (13) << 7)   | \
             (0b0001011 <<  0)   \n" 
             : "+r"(rs1), "=r"(rd)
             : 
             : "a3", "a4"
             );			
        result_rd = rd;
        result_rs1 = rs1;
        if(!((result_rd == 0x21 ) && (result_rs1 == 0x10000004))) {
            errs = errs + 1;
        }
            ///////////////////////////
     // P_LBU_IRPOST
    *(uint8_t*)(0x10002000) = 0x78;
        rs1 = 0x10002000; 
       asm volatile(                         //incr +4 to rs1
            ".word (0b000000000100 << 20) | \
             (     (14) << 15) | \
             (    0b100 << 12) | \
             (    (13) << 7)   | \
             (0b0001011 <<  0)   \n" 
             : "+r"(rs1), "=r"(rd)
             : 
             : "a3", "a4"
             ); 
         result_rd = rd;
        result_rs1 = rs1;                       
        if(!((result_rd == 0x78) && (result_rs1 == 0x10002004))){
        errs = errs + 1;
    }
    ////////////////////
    //P_LH_IRPOST
    *(int16_t*)(0x10000000) = 0x231;
        rs1 = 0x10000000; 
    asm volatile(                         //incr +4 to rs1
            ".word (0b000000000100 << 20) | \
             (     (14) << 15) | \
             (    0b001 << 12) | \
             (    (13) << 7)   | \
             (0b0001011 <<  0)   \n" 
             : "+r"(rs1), "=r"(rd)
             : 
             : "a3", "a4"
             ); 
         result_rd = rd;
        result_rs1 = rs1;                       
        if(!((result_rd == 0x231) && (result_rs1 == 0x10000004))){
        errs = errs + 1;
    }
    /////////////////
    //P_LHU_IRPOST
    *(uint16_t*)(0x10001000) = 0x34;
        rs1 = 0x10001000; 
    asm volatile(                         //incr +4 to rs1
            ".word (0b000000000100 << 20) | \
             (     (14) << 15) | \
             (    0b101 << 12) | \
             (    (13) << 7)   | \
             (0b0001011 <<  0)   \n" 
             : "+r"(rs1), "=r"(rd)
             : 
             : "a3", "a4"
             ); 
         result_rd = rd;
        result_rs1 = rs1;                       
        if(!((result_rd == 0x34) && (result_rs1 == 0x10001004))){
        errs = errs + 1;
    }
    /////////////////
    //P_LW_IRPOST
    *(int32_t*)(0x10000000) = 0x23;
        rs1 = 0x10000000; 
    asm volatile(                         //incr +4 to rs1
            ".word (0b000000000100 << 20) | \
             (     (14) << 15) | \
             (    0b010 << 12) | \
             (    (13) << 7)   | \
             (0b0001011 <<  0)   \n" 
             : "+r"(rs1), "=r"(rd)
             : 
             : "a3", "a4"
             ); 
         result_rd = rd;
        result_rs1 = rs1;                       
        if(!((result_rd == 0x23) && (result_rs1 == 0x10000004 ))){
        errs = errs + 1;
    }

    //////////////////
    //P_LB_RRPOST
    *(int8_t*)(0x10001000) = 0x23;
    register int32_t rs2 asm("a5") = 8; 
    rs1 = 0x10001000; 
    asm volatile(                         //incr +rs2 to rs1
            ".word (0b0000000 << 25) | \
             (     (15) << 20) | \
             (     (14) << 15) | \
             (    0b111 << 12) | \
             (    (13) << 7)   | \
             (0b0001011 <<  0)   \n" 
             : "+r"(rs1), "=r"(rd)
             : "r"(rs2)
             : "a3", "a4", "a5"
             ); 
         result_rd = rd;
        result_rs1 = rs1;                       
        if(!((result_rd == 0x23) && (result_rs1 == 0x10001000 + rs2 ))){
        errs = errs + 1;
    }
    //////////////////
    //P_LBU_RRPOST
    *(uint8_t*)(0x10001800) = 0x57;
    rs2 = 4; 
    rs1 = 0x10001800; 
    asm volatile(                         //incr +rs2 to rs1
            ".word (0b0100000 << 25) | \
             (     (15) << 20) | \
             (     (14) << 15) | \
             (    0b111 << 12) | \
             (    (13) << 7)   | \
             (0b0001011 <<  0)   \n" 
             : "+r"(rs1), "=r"(rd)
             : "r"(rs2)
             : "a3", "a4", "a5"
             ); 
         result_rd = rd;
        result_rs1 = rs1;                       
        if(!((result_rd == 0x57) && (result_rs1 == 0x10001800 + rs2 ))){
        errs = errs + 1;
    }
    ////////////////////
    //P_LH_RRPOST
    *(int16_t*)(0x10001400) = 0x12;
    rs2 = 8; 
    rs1 = 0x10001400; 
     asm volatile(                         //incr +rs2 to rs1
            ".word (0b0001000 << 25) | \
             (     (15) << 20) | \
             (     (14) << 15) | \
             (    0b111 << 12) | \
             (    (13) << 7)   | \
             (0b0001011 <<  0)   \n" 
             : "+r"(rs1), "=r"(rd)
             : "r"(rs2)
             : "a3", "a4", "a5"
             ); 
         result_rd = rd;
        result_rs1 = rs1;                       
        if(!((result_rd == 0x12) && (result_rs1 == 0x10001400 + rs2 ))){
        errs = errs + 1;
    }
    //////////////////
    //P_LHU_RRPOST
    *(uint16_t*)(0x10002400) = 0x41;
    rs2 = 10; 
    rs1 = 0x10002400; 
     asm volatile(                         //incr +rs2 to rs1
            ".word (0b0101000 << 25) | \
             (     (15) << 20) | \
             (     (14) << 15) | \
             (    0b111 << 12) | \
             (    (13) << 7)   | \
             (0b0001011 <<  0)   \n" 
             : "+r"(rs1), "=r"(rd)
             : "r"(rs2)
             : "a3", "a4", "a5"
             ); 
         result_rd = rd;
        result_rs1 = rs1;                       
        if(!((result_rd == 0x41) && (result_rs1 == 0x10002400 + rs2 ))){
        errs = errs + 1;
    }
    ///////////////
    //P_LW_RRPOST 
    *(int32_t*)(0x10002100) = 0x9;
    rs2 = 20; 
    rs1 = 0x10002100; 
     asm volatile(                         //incr +rs2 to rs1
            ".word (0b0010000 << 25) | \
             (     (15) << 20) | \
             (     (14) << 15) | \
             (    0b111 << 12) | \
             (    (13) << 7)   | \
             (0b0001011 <<  0)   \n" 
             : "+r"(rs1), "=r"(rd)
             : "r"(rs2)
             : "a3", "a4", "a5"
             ); 
         result_rd = rd;
        result_rs1 = rs1;                       
        if(!((result_rd == 0x9) && (result_rs1 == 0x10002100 + rs2 ))){
        errs = errs + 1;
    }
    /////////////
    //P_LB_RR
    *(int8_t*)(0x1000200a) = 0x49;
    rs2 = 10; 
    rs1 = 0x10002000; 
     asm volatile(                         //read from rs1 + rs2
            ".word (0b0000000 << 25) | \
             (     (15) << 20) | \
             (     (14) << 15) | \
             (    0b111 << 12) | \
             (    (13) << 7)   | \
             (0b0000011 <<  0)   \n" 
             : "=r"(rd)
             : "r"(rs1), "r"(rs2)
             : "a3", "a4", "a5"
             ); 
         result_rd = rd;
        result_rs1 = rs1;                       
        if(!((result_rd == 0x49) && (result_rs1 == 0x10002000 ))){
        errs = errs + 1;
    }
    ////////////
    //P_LBU_RR
    *(uint8_t*)(0x1000300a) = 0x69;
    rs2 = 10; 
    rs1 = 0x10003000; 
     asm volatile(                         //read from rs1 + rs2
            ".word (0b0100000 << 25) | \
             (     (15) << 20) | \
             (     (14) << 15) | \
             (    0b111 << 12) | \
             (    (13) << 7)   | \
             (0b0000011 <<  0)   \n" 
             : "=r"(rd)
             : "r"(rs1), "r"(rs2)
             : "a3", "a4", "a5"
             ); 
         result_rd = rd;
        result_rs1 = rs1;                       
        if(!((result_rd == 0x69) && (result_rs1 == 0x10003000 ))){
        errs = errs + 1;
    }
    ////////////
    //P_LH_RR
    *(int16_t*)(0x10004004) = 0x25;
    rs2 = 4; 
    rs1 = 0x10004000; 
     asm volatile(                         //read from rs1 + rs2
            ".word (0b0001000 << 25) | \
             (     (15) << 20) | \
             (     (14) << 15) | \
             (    0b111 << 12) | \
             (    (13) << 7)   | \
             (0b0000011 <<  0)   \n" 
             : "=r"(rd)
             : "r"(rs1), "r"(rs2)
             : "a3", "a4", "a5"
             ); 
         result_rd = rd;
        result_rs1 = rs1;                       
        if(!((result_rd == 0x25) && (result_rs1 == 0x10004000 ))){
        errs = errs + 1;
    }
    ////////////
    //P_LHU_RR
    *(uint16_t*)(0x10003008) = 0x11;
    rs2 = 8; 
    rs1 = 0x10003000; 
     asm volatile(                         //read from rs1 + rs2
            ".word (0b0001000 << 25) | \
             (     (15) << 20) | \
             (     (14) << 15) | \
             (    0b111 << 12) | \
             (    (13) << 7)   | \
             (0b0000011 <<  0)   \n" 
             : "=r"(rd)
             : "r"(rs1), "r"(rs2)
             : "a3", "a4", "a5"
             ); 
         result_rd = rd;
        result_rs1 = rs1;                       
        if(!((result_rd == 0x11) && (result_rs1 == 0x10003000 ))){
        errs = errs + 1;
    }
    ///////////
    //P_LW_RR
   *(int32_t*)(0x10009004) = 0x33;
    rs2 = 4; 
    rs1 = 0x10009000; 
     asm volatile(                         //read from rs1 + rs2
            ".word (0b0010000 << 25) | \
             (     (15) << 20) | \
             (     (14) << 15) | \
             (    0b111 << 12) | \
             (    (13) << 7)   | \
             (0b0000011 <<  0)   \n" 
             : "=r"(rd)
             : "r"(rs1), "r"(rs2)
             : "a3", "a4", "a5"
             ); 
         result_rd = rd;
        result_rs1 = rs1;                       
        if(!((result_rd == 0x33) && (result_rs1 == 0x10009000 ))){
        errs = errs + 1;
    }
    ////////////
    //P_SB_IRPOST
    rs2 = 0x76;
    rs1 = 0x10000000; 
     asm volatile(                         //write rs2 value to rs1, increment rs1
            ".word (0b0000000 << 25) | \
             (     (15) << 20) | \
             (     (14) << 15) | \
             (    0b000 << 12) | \
             (    0b00100 << 7)   | \
             (0b0101011 <<  0)   \n" 
             : "+r"(rs1)
             : "r"(rs2)
             : "a3", "a4"
             ); 
        result_rd = *(int8_t*)(0x10000000);
        result_rs1 = rs1; 
        if(!((result_rd == 0x76) && (result_rs1 == 0x10000004 ))){
            errs = errs + 1;
    }
    //////////
    //P_SH_IRPOST
    rs2 = 0x99;
    rs1 = 0x10001000; 
     asm volatile(                         //write rs2 value to rs1, increment rs1
            ".word (0b0000000 << 25) | \
             (     (15) << 20) | \
             (     (14) << 15) | \
             (    0b001 << 12) | \
             (    0b00100 << 7)   | \
             (0b0101011 <<  0)   \n" 
             : "+r"(rs1)
             : "r"(rs2)
             : "a3", "a4"
             ); 
        result_rd = *(int16_t*)(0x10001000);
        result_rs1 = rs1; 
        if(!((result_rd == 0x99) && (result_rs1 == 0x10001004 ))){
            errs = errs + 1;
    }
    //////////
    //P_SW_IRPOST
    rs2 = 0x71;
    rs1 = 0x10001100; 
     asm volatile(                         //write rs2 value to rs1, increment rs1
            ".word (0b0000000 << 25) | \
             (     (15) << 20) | \
             (     (14) << 15) | \
             (    0b010 << 12) | \
             (    0b00100 << 7)   | \
             (0b0101011 <<  0)   \n" 
             : "+r"(rs1)
             : "r"(rs2)
             : "a3", "a4"
             ); 
        result_rd = *(int32_t*)(0x10001100);
        result_rs1 = rs1; 
        if(!((result_rd == 0x71) && (result_rs1 == 0x10001104 ))){
            errs = errs + 1;
    }


        return errs;
        } else return 0;
        snrt_cluster_hw_barrier();
    return 0;
} 

/*int main() {
uint32_t core_id = snrt_global_core_num();
   snrt_cluster_hw_barrier();
   if (core_id == 2) {
   //	printf("Hello, World!\n");
        int errs = 0;
	int32_t result_rd;
        int32_t result_rs1;
	int8_t *mem8 = (int8_t *)0x10000000;
	mem8[0] = 0x21;
	volatile register int32_t rd asm("a3") = 1;   
        volatile register int32_t rs1 asm("a4") = 0x10000000; // rs1, data source
        // P_LB_IRPOST
       asm volatile(                         //incr +4 to rs1
            ".word (0b000000000100 << 20) | \
             (     (14) << 15) | \
             (    0b000 << 12) | \
             (    (13) << 7)   | \
             (0b0001011 <<  0)   \n" 
             : "+r"(rs1), "=r"(rd)
             : 
             : "a3", "a4"
             );			
        result_rd = rd;
        result_rs1 = rs1;
     //   printf("test %d", result_rd);				 		
        if(((result_rd == 0x21 ) && (result_rs1 == 0x10000004))){
       //	printf("test %d", result_rd);
       	 errs = errs + 1;
        return errs;
        }			
         }
            return 0;
}   */
/*	int8_t *mem9 = (int8_t *)0x100000d4;	//  Strange thing, If the programm reads from this address the result is 0.
	*(int8_t*)(0x100000d0) = 0x89;		//  Are there some issues with Shifts that I don't know??
	mem9[0] = 0x55;				// Also return err; doesn't work!
	volatile int8_t *ptr1 = (int8_t *)0x100000d0;
	int8_t val1 = *ptr1; 
        rs1 = 0x100000d0;
	asm volatile(                         //incr +4 to rs1
            ".word (0b000000000100 << 20) | \
             (     (14) << 15) | \
             (    0b000 << 12) | \
             (    (13) << 7)   | \
             (0b0001011 <<  0)   \n" 
             : "+r"(rs1), "=r"(rd)
             : 
             : "a3", "a4"
             );	
        result_rd = rd;
        result_rs1 = rs1;			 		
        if(!((result_rd == 0x100000d4) && (result_rs1 == 0x89))){
        errs = errs - 1;
        }
        *(int8_t*)(0x10001000) = 0x34;
        rs1 = 0x10001000;
        volatile int8_t *ptr2 = (int8_t *)0x10001000;
	int8_t val2 = *ptr2;  
            snrt_cluster_hw_barrier();
       asm volatile(                         //incr +4 to rs1
            ".word (0b000000000100 << 20) | \
             (     (14) << 15) | \
             (    0b000 << 12) | \
             (    (13) << 7)   | \
             (0b0001011 <<  0)   \n" 
             : "+r"(rs1), "=r"(rd)
             : 
             : "a3", "a4"
             );	
         result_rd = rd;
        result_rs1 = rs1;				 		
        if(!((result_rd == 0x10001004) && (result_rs1 == 0x34))){
        errs = errs - 1;
	}
	
	///////////////////////////
	 // P_LBU_IRPOST
	*(uint8_t*)(0x10002000) = 0x78;
        rs1 = 0x10002000; 
       asm volatile(                         //incr +4 to rs1
            ".word (0b000000000100 << 20) | \
             (     (14) << 15) | \
             (    0b100 << 12) | \
             (    (13) << 7)   | \
             (0b0001011 <<  0)   \n" 
             : "+r"(rs1), "=r"(rd)
             : 
             : "a3", "a4"
             );	
         result_rd = rd;
        result_rs1 = rs1;				 		
        if(!((result_rd == 0x10002004) && (result_rs1 == 0x78))){
        errs = errs - 1;
	}
	////////////////////
	//P_LH_IRPOST
	*(int16_t*)(0x10000000) = 0x231;
        rs1 = 0x10000000; 
	asm volatile(                         //incr +4 to rs1
            ".word (0b000000000100 << 20) | \
             (     (14) << 15) | \
             (    0b001 << 12) | \
             (    (13) << 7)   | \
             (0b0001011 <<  0)   \n" 
             : "+r"(rs1), "=r"(rd)
             : 
             : "a3", "a4"
             );	
         result_rd = rd;
        result_rs1 = rs1;				 		
        if(!((result_rd == 0x10000004) && (result_rs1 == 0x231))){
        errs = errs - 1;
	}
	/////////////////
	//P_LHU_IRPOST
	*(uint16_t*)(0x10001000) = 0x34;
        rs1 = 0x10001000; 
	asm volatile(                         //incr +4 to rs1
            ".word (0b000000000100 << 20) | \
             (     (14) << 15) | \
             (    0b101 << 12) | \
             (    (13) << 7)   | \
             (0b0001011 <<  0)   \n" 
             : "+r"(rs1), "=r"(rd)
             : 
             : "a3", "a4"
             );	
         result_rd = rd;
        result_rs1 = rs1;				 		
        if(!((result_rd == 0x10001004) && (result_rs1 == 0x34))){
        errs = errs - 1;
	}
	/////////////////
	//P_LW_IRPOST
	*(int32_t*)(0x100002000) = 0x23;
        rs1 = 0x10002000; 
	asm volatile(                         //incr +4 to rs1
            ".word (0b000000000100 << 20) | \
             (     (14) << 15) | \
             (    0b010 << 12) | \
             (    (13) << 7)   | \
             (0b0001011 <<  0)   \n" 
             : "+r"(rs1), "=r"(rd)
             : 
             : "a3", "a4"
             );	
         result_rd = rd;
        result_rs1 = rs1;				 		
        if(!((result_rd == 0x10002004) && (result_rs1 == 0x23))){
        errs = errs - 1;
	}
	//////////////////
	//P_LB_RRPOST
	*(int8_t*)(0x100000000) = 0x23;
	volatile register int32_t rs2 asm("a5") = 4; 
        rs1 = 0x10000000; 
	asm volatile(                         //incr +4 to rs1
            ".word (0b0000000 << 25) | \
             (     (15) << 20) | \
             (     (14) << 15) | \
             (    0b010 << 12) | \
             (    (13) << 7)   | \
             (0b0001011 <<  0)   \n" 
             : "+r"(rs1), "=r"(rd)
             : "r"(rs2)
             : "a3", "a4", "a5"
             );	
          rs2 = rs2 + 3;
         result_rd = rd;
        result_rs1 = rs1;				 		
        if(!((result_rd == 0x10000004) && (result_rs1 == 0x23))){
        errs = errs - 1;
	}
		*/
       
    
