﻿

/*
static void doPrecomputation()
{
	uint bitmaps[1024];

	int indices[16];
	int num = 0;

	// Compute bitmaps with 3 clusters:

	// first cluster [0,i) is at the start
	for( int m = 0; m < 16; ++m )
	{
		indices[m] = 0;
	}
	const int imax = 15;
	for( int i = imax; i >= 0; --i )
	{
		// second cluster [i,j) is half along
		for( int m = i; m < 16; ++m )
		{
			indices[m] = 2;
		}
		const int jmax = ( i == 0 ) ? 15 : 16;
		for( int j = jmax; j >= i; --j )
		{
			// last cluster [j,k) is at the end
			if( j < 16 )
			{
				indices[j] = 1;
			}
			
			uint bitmap = 0;
			
			for(int p = 0; p < 16; p++) {
				bitmap |= indices[p] << (p * 2);
			}
				
			bitmaps[num] = bitmap;
			
			num++;
		}
	}
	nvDebugCheck(num == 151);

	// Align to 160.
	for(int i = 0; i < 9; i++)
	{
		bitmaps[num] = 0x555AA000;
		num++;
	}
	nvDebugCheck(num == 160);

	// Append bitmaps with 4 clusters:

	// first cluster [0,i) is at the start
	for( int m = 0; m < 16; ++m )
	{
		indices[m] = 0;
	}
	for( int i = imax; i >= 0; --i )
	{
		// second cluster [i,j) is one third along
		for( int m = i; m < 16; ++m )
		{
			indices[m] = 2;
		}
		const int jmax = ( i == 0 ) ? 15 : 16;
		for( int j = jmax; j >= i; --j )
		{
			// third cluster [j,k) is two thirds along
			for( int m = j; m < 16; ++m )
			{
				indices[m] = 3;
			}
			
			int kmax = ( j == 0 ) ? 15 : 16;
			for( int k = kmax; k >= j; --k )
			{
				// last cluster [k,n) is at the end
				if( k < 16 )
				{
					indices[k] = 1;
				}
				
				uint bitmap = 0;
				
				bool hasThree = false;
				for(int p = 0; p < 16; p++) {
					bitmap |= indices[p] << (p * 2);
					
					if (indices[p] == 3) hasThree = true;
				}
				
				if (hasThree) {
					bitmaps[num] = bitmap;
					num++;
				}
			}
		}
	}
	nvDebugCheck(num == 975);
	
	// Align to 1024.
	for(int i = 0; i < 49; i++)
	{
		bitmaps[num] = 0x555AA000;
		num++;
	}

	nvDebugCheck(num == 1024);

	printf("uint bitmaps[992] =\n{\n");
	for (int i = 0; i < 992; i++)
	{
		printf("\t0x%.8X,\n", bitmaps[i]);
	}
	printf("};\n");
}
*/

const static uint s_bitmapTable[992] = {
    0x80000000,
    0x40000000,
    0xA0000000,
    0x60000000,
    0x50000000,
    0xA8000000,
    0x68000000,
    0x58000000,
    0x54000000,
    0xAA000000,
    0x6A000000,
    0x5A000000,
    0x56000000,
    0x55000000,
    0xAA800000,
    0x6A800000,
    0x5A800000,
    0x56800000,
    0x55800000,
    0x55400000,
    0xAAA00000,
    0x6AA00000,
    0x5AA00000,
    0x56A00000,
    0x55A00000,
    0x55600000,
    0x55500000,
    0xAAA80000,
    0x6AA80000,
    0x5AA80000,
    0x56A80000,
    0x55A80000,
    0x55680000,
    0x55580000,
    0x55540000,
    0xAAAA0000,
    0x6AAA0000,
    0x5AAA0000,
    0x56AA0000,
    0x55AA0000,
    0x556A0000,
    0x555A0000,
    0x55560000,
    0x55550000,
    0xAAAA8000,
    0x6AAA8000,
    0x5AAA8000,
    0x56AA8000,
    0x55AA8000,
    0x556A8000,
    0x555A8000,
    0x55568000,
    0x55558000,
    0x55554000,
    0xAAAAA000,
    0x6AAAA000,
    0x5AAAA000,
    0x56AAA000,
    0x55AAA000,
    0x556AA000,
    0x555AA000,
    0x5556A000,
    0x5555A000,
    0x55556000,
    0x55555000,
    0xAAAAA800,
    0x6AAAA800,
    0x5AAAA800,
    0x56AAA800,
    0x55AAA800,
    0x556AA800,
    0x555AA800,
    0x5556A800,
    0x5555A800,
    0x55556800,
    0x55555800,
    0x55555400,
    0xAAAAAA00,
    0x6AAAAA00,
    0x5AAAAA00,
    0x56AAAA00,
    0x55AAAA00,
    0x556AAA00,
    0x555AAA00,
    0x5556AA00,
    0x5555AA00,
    0x55556A00,
    0x55555A00,
    0x55555600,
    0x55555500,
    0xAAAAAA80,
    0x6AAAAA80,
    0x5AAAAA80,
    0x56AAAA80,
    0x55AAAA80,
    0x556AAA80,
    0x555AAA80,
    0x5556AA80,
    0x5555AA80,
    0x55556A80,
    0x55555A80,
    0x55555680,
    0x55555580,
    0x55555540,
    0xAAAAAAA0,
    0x6AAAAAA0,
    0x5AAAAAA0,
    0x56AAAAA0,
    0x55AAAAA0,
    0x556AAAA0,
    0x555AAAA0,
    0x5556AAA0,
    0x5555AAA0,
    0x55556AA0,
    0x55555AA0,
    0x555556A0,
    0x555555A0,
    0x55555560,
    0x55555550,
    0xAAAAAAA8,
    0x6AAAAAA8,
    0x5AAAAAA8,
    0x56AAAAA8,
    0x55AAAAA8,
    0x556AAAA8,
    0x555AAAA8,
    0x5556AAA8,
    0x5555AAA8,
    0x55556AA8,
    0x55555AA8,
    0x555556A8,
    0x555555A8,
    0x55555568,
    0x55555558,
    0x55555554,
    0x6AAAAAAA,
    0x5AAAAAAA,
    0x56AAAAAA,
    0x55AAAAAA,
    0x556AAAAA,
    0x555AAAAA,
    0x5556AAAA,
    0x5555AAAA,
    0x55556AAA,
    0x55555AAA,
    0x555556AA,
    0x555555AA,
    0x5555556A,
    0x5555555A,
    0x55555556,
    0x55555555,
    0x55555555,
    0x55555555,
    0x55555555,
    0x55555555,
    0x55555555,
    0x55555555,
    0x55555555,
    0x55555555,
    0x55555555,
    0xC0000000,
    0xE0000000,
    0xF0000000,
    0x70000000,
    0xE8000000,
    0xF8000000,
    0x78000000,
    0xFC000000,
    0x7C000000,
    0x5C000000,
    0xEA000000,
    0xFA000000,
    0x7A000000,
    0xFE000000,
    0x7E000000,
    0x5E000000,
    0xFF000000,
    0x7F000000,
    0x5F000000,
    0x57000000,
    0xEA800000,
    0xFA800000,
    0x7A800000,
    0xFE800000,
    0x7E800000,
    0x5E800000,
    0xFF800000,
    0x7F800000,
    0x5F800000,
    0x57800000,
    0xFFC00000,
    0x7FC00000,
    0x5FC00000,
    0x57C00000,
    0x55C00000,
    0xEAA00000,
    0xFAA00000,
    0x7AA00000,
    0xFEA00000,
    0x7EA00000,
    0x5EA00000,
    0xFFA00000,
    0x7FA00000,
    0x5FA00000,
    0x57A00000,
    0xFFE00000,
    0x7FE00000,
    0x5FE00000,
    0x57E00000,
    0x55E00000,
    0xFFF00000,
    0x7FF00000,
    0x5FF00000,
    0x57F00000,
    0x55F00000,
    0x55700000,
    0xEAA80000,
    0xFAA80000,
    0x7AA80000,
    0xFEA80000,
    0x7EA80000,
    0x5EA80000,
    0xFFA80000,
    0x7FA80000,
    0x5FA80000,
    0x57A80000,
    0xFFE80000,
    0x7FE80000,
    0x5FE80000,
    0x57E80000,
    0x55E80000,
    0xFFF80000,
    0x7FF80000,
    0x5FF80000,
    0x57F80000,
    0x55F80000,
    0x55780000,
    0xFFFC0000,
    0x7FFC0000,
    0x5FFC0000,
    0x57FC0000,
    0x55FC0000,
    0x557C0000,
    0x555C0000,
    0xEAAA0000,
    0xFAAA0000,
    0x7AAA0000,
    0xFEAA0000,
    0x7EAA0000,
    0x5EAA0000,
    0xFFAA0000,
    0x7FAA0000,
    0x5FAA0000,
    0x57AA0000,
    0xFFEA0000,
    0x7FEA0000,
    0x5FEA0000,
    0x57EA0000,
    0x55EA0000,
    0xFFFA0000,
    0x7FFA0000,
    0x5FFA0000,
    0x57FA0000,
    0x55FA0000,
    0x557A0000,
    0xFFFE0000,
    0x7FFE0000,
    0x5FFE0000,
    0x57FE0000,
    0x55FE0000,
    0x557E0000,
    0x555E0000,
    0xFFFF0000,
    0x7FFF0000,
    0x5FFF0000,
    0x57FF0000,
    0x55FF0000,
    0x557F0000,
    0x555F0000,
    0x55570000,
    0xEAAA8000,
    0xFAAA8000,
    0x7AAA8000,
    0xFEAA8000,
    0x7EAA8000,
    0x5EAA8000,
    0xFFAA8000,
    0x7FAA8000,
    0x5FAA8000,
    0x57AA8000,
    0xFFEA8000,
    0x7FEA8000,
    0x5FEA8000,
    0x57EA8000,
    0x55EA8000,
    0xFFFA8000,
    0x7FFA8000,
    0x5FFA8000,
    0x57FA8000,
    0x55FA8000,
    0x557A8000,
    0xFFFE8000,
    0x7FFE8000,
    0x5FFE8000,
    0x57FE8000,
    0x55FE8000,
    0x557E8000,
    0x555E8000,
    0xFFFF8000,
    0x7FFF8000,
    0x5FFF8000,
    0x57FF8000,
    0x55FF8000,
    0x557F8000,
    0x555F8000,
    0x55578000,
    0xFFFFC000,
    0x7FFFC000,
    0x5FFFC000,
    0x57FFC000,
    0x55FFC000,
    0x557FC000,
    0x555FC000,
    0x5557C000,
    0x5555C000,
    0xEAAAA000,
    0xFAAAA000,
    0x7AAAA000,
    0xFEAAA000,
    0x7EAAA000,
    0x5EAAA000,
    0xFFAAA000,
    0x7FAAA000,
    0x5FAAA000,
    0x57AAA000,
    0xFFEAA000,
    0x7FEAA000,
    0x5FEAA000,
    0x57EAA000,
    0x55EAA000,
    0xFFFAA000,
    0x7FFAA000,
    0x5FFAA000,
    0x57FAA000,
    0x55FAA000,
    0x557AA000,
    0xFFFEA000,
    0x7FFEA000,
    0x5FFEA000,
    0x57FEA000,
    0x55FEA000,
    0x557EA000,
    0x555EA000,
    0xFFFFA000,
    0x7FFFA000,
    0x5FFFA000,
    0x57FFA000,
    0x55FFA000,
    0x557FA000,
    0x555FA000,
    0x5557A000,
    0xFFFFE000,
    0x7FFFE000,
    0x5FFFE000,
    0x57FFE000,
    0x55FFE000,
    0x557FE000,
    0x555FE000,
    0x5557E000,
    0x5555E000,
    0xFFFFF000,
    0x7FFFF000,
    0x5FFFF000,
    0x57FFF000,
    0x55FFF000,
    0x557FF000,
    0x555FF000,
    0x5557F000,
    0x5555F000,
    0x55557000,
    0xEAAAA800,
    0xFAAAA800,
    0x7AAAA800,
    0xFEAAA800,
    0x7EAAA800,
    0x5EAAA800,
    0xFFAAA800,
    0x7FAAA800,
    0x5FAAA800,
    0x57AAA800,
    0xFFEAA800,
    0x7FEAA800,
    0x5FEAA800,
    0x57EAA800,
    0x55EAA800,
    0xFFFAA800,
    0x7FFAA800,
    0x5FFAA800,
    0x57FAA800,
    0x55FAA800,
    0x557AA800,
    0xFFFEA800,
    0x7FFEA800,
    0x5FFEA800,
    0x57FEA800,
    0x55FEA800,
    0x557EA800,
    0x555EA800,
    0xFFFFA800,
    0x7FFFA800,
    0x5FFFA800,
    0x57FFA800,
    0x55FFA800,
    0x557FA800,
    0x555FA800,
    0x5557A800,
    0xFFFFE800,
    0x7FFFE800,
    0x5FFFE800,
    0x57FFE800,
    0x55FFE800,
    0x557FE800,
    0x555FE800,
    0x5557E800,
    0x5555E800,
    0xFFFFF800,
    0x7FFFF800,
    0x5FFFF800,
    0x57FFF800,
    0x55FFF800,
    0x557FF800,
    0x555FF800,
    0x5557F800,
    0x5555F800,
    0x55557800,
    0xFFFFFC00,
    0x7FFFFC00,
    0x5FFFFC00,
    0x57FFFC00,
    0x55FFFC00,
    0x557FFC00,
    0x555FFC00,
    0x5557FC00,
    0x5555FC00,
    0x55557C00,
    0x55555C00,
    0xEAAAAA00,
    0xFAAAAA00,
    0x7AAAAA00,
    0xFEAAAA00,
    0x7EAAAA00,
    0x5EAAAA00,
    0xFFAAAA00,
    0x7FAAAA00,
    0x5FAAAA00,
    0x57AAAA00,
    0xFFEAAA00,
    0x7FEAAA00,
    0x5FEAAA00,
    0x57EAAA00,
    0x55EAAA00,
    0xFFFAAA00,
    0x7FFAAA00,
    0x5FFAAA00,
    0x57FAAA00,
    0x55FAAA00,
    0x557AAA00,
    0xFFFEAA00,
    0x7FFEAA00,
    0x5FFEAA00,
    0x57FEAA00,
    0x55FEAA00,
    0x557EAA00,
    0x555EAA00,
    0xFFFFAA00,
    0x7FFFAA00,
    0x5FFFAA00,
    0x57FFAA00,
    0x55FFAA00,
    0x557FAA00,
    0x555FAA00,
    0x5557AA00,
    0xFFFFEA00,
    0x7FFFEA00,
    0x5FFFEA00,
    0x57FFEA00,
    0x55FFEA00,
    0x557FEA00,
    0x555FEA00,
    0x5557EA00,
    0x5555EA00,
    0xFFFFFA00,
    0x7FFFFA00,
    0x5FFFFA00,
    0x57FFFA00,
    0x55FFFA00,
    0x557FFA00,
    0x555FFA00,
    0x5557FA00,
    0x5555FA00,
    0x55557A00,
    0xFFFFFE00,
    0x7FFFFE00,
    0x5FFFFE00,
    0x57FFFE00,
    0x55FFFE00,
    0x557FFE00,
    0x555FFE00,
    0x5557FE00,
    0x5555FE00,
    0x55557E00,
    0x55555E00,
    0xFFFFFF00,
    0x7FFFFF00,
    0x5FFFFF00,
    0x57FFFF00,
    0x55FFFF00,
    0x557FFF00,
    0x555FFF00,
    0x5557FF00,
    0x5555FF00,
    0x55557F00,
    0x55555F00,
    0x55555700,
    0xEAAAAA80,
    0xFAAAAA80,
    0x7AAAAA80,
    0xFEAAAA80,
    0x7EAAAA80,
    0x5EAAAA80,
    0xFFAAAA80,
    0x7FAAAA80,
    0x5FAAAA80,
    0x57AAAA80,
    0xFFEAAA80,
    0x7FEAAA80,
    0x5FEAAA80,
    0x57EAAA80,
    0x55EAAA80,
    0xFFFAAA80,
    0x7FFAAA80,
    0x5FFAAA80,
    0x57FAAA80,
    0x55FAAA80,
    0x557AAA80,
    0xFFFEAA80,
    0x7FFEAA80,
    0x5FFEAA80,
    0x57FEAA80,
    0x55FEAA80,
    0x557EAA80,
    0x555EAA80,
    0xFFFFAA80,
    0x7FFFAA80,
    0x5FFFAA80,
    0x57FFAA80,
    0x55FFAA80,
    0x557FAA80,
    0x555FAA80,
    0x5557AA80,
    0xFFFFEA80,
    0x7FFFEA80,
    0x5FFFEA80,
    0x57FFEA80,
    0x55FFEA80,
    0x557FEA80,
    0x555FEA80,
    0x5557EA80,
    0x5555EA80,
    0xFFFFFA80,
    0x7FFFFA80,
    0x5FFFFA80,
    0x57FFFA80,
    0x55FFFA80,
    0x557FFA80,
    0x555FFA80,
    0x5557FA80,
    0x5555FA80,
    0x55557A80,
    0xFFFFFE80,
    0x7FFFFE80,
    0x5FFFFE80,
    0x57FFFE80,
    0x55FFFE80,
    0x557FFE80,
    0x555FFE80,
    0x5557FE80,
    0x5555FE80,
    0x55557E80,
    0x55555E80,
    0xFFFFFF80,
    0x7FFFFF80,
    0x5FFFFF80,
    0x57FFFF80,
    0x55FFFF80,
    0x557FFF80,
    0x555FFF80,
    0x5557FF80,
    0x5555FF80,
    0x55557F80,
    0x55555F80,
    0x55555780,
    0xFFFFFFC0,
    0x7FFFFFC0,
    0x5FFFFFC0,
    0x57FFFFC0,
    0x55FFFFC0,
    0x557FFFC0,
    0x555FFFC0,
    0x5557FFC0,
    0x5555FFC0,
    0x55557FC0,
    0x55555FC0,
    0x555557C0,
    0x555555C0,
    0xEAAAAAA0,
    0xFAAAAAA0,
    0x7AAAAAA0,
    0xFEAAAAA0,
    0x7EAAAAA0,
    0x5EAAAAA0,
    0xFFAAAAA0,
    0x7FAAAAA0,
    0x5FAAAAA0,
    0x57AAAAA0,
    0xFFEAAAA0,
    0x7FEAAAA0,
    0x5FEAAAA0,
    0x57EAAAA0,
    0x55EAAAA0,
    0xFFFAAAA0,
    0x7FFAAAA0,
    0x5FFAAAA0,
    0x57FAAAA0,
    0x55FAAAA0,
    0x557AAAA0,
    0xFFFEAAA0,
    0x7FFEAAA0,
    0x5FFEAAA0,
    0x57FEAAA0,
    0x55FEAAA0,
    0x557EAAA0,
    0x555EAAA0,
    0xFFFFAAA0,
    0x7FFFAAA0,
    0x5FFFAAA0,
    0x57FFAAA0,
    0x55FFAAA0,
    0x557FAAA0,
    0x555FAAA0,
    0x5557AAA0,
    0xFFFFEAA0,
    0x7FFFEAA0,
    0x5FFFEAA0,
    0x57FFEAA0,
    0x55FFEAA0,
    0x557FEAA0,
    0x555FEAA0,
    0x5557EAA0,
    0x5555EAA0,
    0xFFFFFAA0,
    0x7FFFFAA0,
    0x5FFFFAA0,
    0x57FFFAA0,
    0x55FFFAA0,
    0x557FFAA0,
    0x555FFAA0,
    0x5557FAA0,
    0x5555FAA0,
    0x55557AA0,
    0xFFFFFEA0,
    0x7FFFFEA0,
    0x5FFFFEA0,
    0x57FFFEA0,
    0x55FFFEA0,
    0x557FFEA0,
    0x555FFEA0,
    0x5557FEA0,
    0x5555FEA0,
    0x55557EA0,
    0x55555EA0,
    0xFFFFFFA0,
    0x7FFFFFA0,
    0x5FFFFFA0,
    0x57FFFFA0,
    0x55FFFFA0,
    0x557FFFA0,
    0x555FFFA0,
    0x5557FFA0,
    0x5555FFA0,
    0x55557FA0,
    0x55555FA0,
    0x555557A0,
    0xFFFFFFE0,
    0x7FFFFFE0,
    0x5FFFFFE0,
    0x57FFFFE0,
    0x55FFFFE0,
    0x557FFFE0,
    0x555FFFE0,
    0x5557FFE0,
    0x5555FFE0,
    0x55557FE0,
    0x55555FE0,
    0x555557E0,
    0x555555E0,
    0xFFFFFFF0,
    0x7FFFFFF0,
    0x5FFFFFF0,
    0x57FFFFF0,
    0x55FFFFF0,
    0x557FFFF0,
    0x555FFFF0,
    0x5557FFF0,
    0x5555FFF0,
    0x55557FF0,
    0x55555FF0,
    0x555557F0,
    0x555555F0,
    0x55555570,
    0xEAAAAAA8,
    0xFAAAAAA8,
    0x7AAAAAA8,
    0xFEAAAAA8,
    0x7EAAAAA8,
    0x5EAAAAA8,
    0xFFAAAAA8,
    0x7FAAAAA8,
    0x5FAAAAA8,
    0x57AAAAA8,
    0xFFEAAAA8,
    0x7FEAAAA8,
    0x5FEAAAA8,
    0x57EAAAA8,
    0x55EAAAA8,
    0xFFFAAAA8,
    0x7FFAAAA8,
    0x5FFAAAA8,
    0x57FAAAA8,
    0x55FAAAA8,
    0x557AAAA8,
    0xFFFEAAA8,
    0x7FFEAAA8,
    0x5FFEAAA8,
    0x57FEAAA8,
    0x55FEAAA8,
    0x557EAAA8,
    0x555EAAA8,
    0xFFFFAAA8,
    0x7FFFAAA8,
    0x5FFFAAA8,
    0x57FFAAA8,
    0x55FFAAA8,
    0x557FAAA8,
    0x555FAAA8,
    0x5557AAA8,
    0xFFFFEAA8,
    0x7FFFEAA8,
    0x5FFFEAA8,
    0x57FFEAA8,
    0x55FFEAA8,
    0x557FEAA8,
    0x555FEAA8,
    0x5557EAA8,
    0x5555EAA8,
    0xFFFFFAA8,
    0x7FFFFAA8,
    0x5FFFFAA8,
    0x57FFFAA8,
    0x55FFFAA8,
    0x557FFAA8,
    0x555FFAA8,
    0x5557FAA8,
    0x5555FAA8,
    0x55557AA8,
    0xFFFFFEA8,
    0x7FFFFEA8,
    0x5FFFFEA8,
    0x57FFFEA8,
    0x55FFFEA8,
    0x557FFEA8,
    0x555FFEA8,
    0x5557FEA8,
    0x5555FEA8,
    0x55557EA8,
    0x55555EA8,
    0xFFFFFFA8,
    0x7FFFFFA8,
    0x5FFFFFA8,
    0x57FFFFA8,
    0x55FFFFA8,
    0x557FFFA8,
    0x555FFFA8,
    0x5557FFA8,
    0x5555FFA8,
    0x55557FA8,
    0x55555FA8,
    0x555557A8,
    0xFFFFFFE8,
    0x7FFFFFE8,
    0x5FFFFFE8,
    0x57FFFFE8,
    0x55FFFFE8,
    0x557FFFE8,
    0x555FFFE8,
    0x5557FFE8,
    0x5555FFE8,
    0x55557FE8,
    0x55555FE8,
    0x555557E8,
    0x555555E8,
    0xFFFFFFF8,
    0x7FFFFFF8,
    0x5FFFFFF8,
    0x57FFFFF8,
    0x55FFFFF8,
    0x557FFFF8,
    0x555FFFF8,
    0x5557FFF8,
    0x5555FFF8,
    0x55557FF8,
    0x55555FF8,
    0x555557F8,
    0x555555F8,
    0x55555578,
    0xFFFFFFFC,
    0x7FFFFFFC,
    0x5FFFFFFC,
    0x57FFFFFC,
    0x55FFFFFC,
    0x557FFFFC,
    0x555FFFFC,
    0x5557FFFC,
    0x5555FFFC,
    0x55557FFC,
    0x55555FFC,
    0x555557FC,
    0x555555FC,
    0x5555557C,
    0x5555555C,
    0xEAAAAAAA,
    0xFAAAAAAA,
    0x7AAAAAAA,
    0xFEAAAAAA,
    0x7EAAAAAA,
    0x5EAAAAAA,
    0xFFAAAAAA,
    0x7FAAAAAA,
    0x5FAAAAAA,
    0x57AAAAAA,
    0xFFEAAAAA,
    0x7FEAAAAA,
    0x5FEAAAAA,
    0x57EAAAAA,
    0x55EAAAAA,
    0xFFFAAAAA,
    0x7FFAAAAA,
    0x5FFAAAAA,
    0x57FAAAAA,
    0x55FAAAAA,
    0x557AAAAA,
    0xFFFEAAAA,
    0x7FFEAAAA,
    0x5FFEAAAA,
    0x57FEAAAA,
    0x55FEAAAA,
    0x557EAAAA,
    0x555EAAAA,
    0xFFFFAAAA,
    0x7FFFAAAA,
    0x5FFFAAAA,
    0x57FFAAAA,
    0x55FFAAAA,
    0x557FAAAA,
    0x555FAAAA,
    0x5557AAAA,
    0xFFFFEAAA,
    0x7FFFEAAA,
    0x5FFFEAAA,
    0x57FFEAAA,
    0x55FFEAAA,
    0x557FEAAA,
    0x555FEAAA,
    0x5557EAAA,
    0x5555EAAA,
    0xFFFFFAAA,
    0x7FFFFAAA,
    0x5FFFFAAA,
    0x57FFFAAA,
    0x55FFFAAA,
    0x557FFAAA,
    0x555FFAAA,
    0x5557FAAA,
    0x5555FAAA,
    0x55557AAA,
    0xFFFFFEAA,
    0x7FFFFEAA,
    0x5FFFFEAA,
    0x57FFFEAA,
    0x55FFFEAA,
    0x557FFEAA,
    0x555FFEAA,
    0x5557FEAA,
    0x5555FEAA,
    0x55557EAA,
    0x55555EAA,
    0xFFFFFFAA,
    0x7FFFFFAA,
    0x5FFFFFAA,
    0x57FFFFAA,
    0x55FFFFAA,
    0x557FFFAA,
    0x555FFFAA,
    0x5557FFAA,
    0x5555FFAA,
    0x55557FAA,
    0x55555FAA,
    0x555557AA,
    0xFFFFFFEA,
    0x7FFFFFEA,
    0x5FFFFFEA,
    0x57FFFFEA,
    0x55FFFFEA,
    0x557FFFEA,
    0x555FFFEA,
    0x5557FFEA,
    0x5555FFEA,
    0x55557FEA,
    0x55555FEA,
    0x555557EA,
    0x555555EA,
    0xFFFFFFFA,
    0x7FFFFFFA,
    0x5FFFFFFA,
    0x57FFFFFA,
    0x55FFFFFA,
    0x557FFFFA,
    0x555FFFFA,
    0x5557FFFA,
    0x5555FFFA,
    0x55557FFA,
    0x55555FFA,
    0x555557FA,
    0x555555FA,
    0x5555557A,
    0xFFFFFFFE,
    0x7FFFFFFE,
    0x5FFFFFFE,
    0x57FFFFFE,
    0x55FFFFFE,
    0x557FFFFE,
    0x555FFFFE,
    0x5557FFFE,
    0x5555FFFE,
    0x55557FFE,
    0x55555FFE,
    0x555557FE,
    0x555555FE,
    0x5555557E,
    0x5555555E,
    0x7FFFFFFF,
    0x5FFFFFFF,
    0x57FFFFFF,
    0x55FFFFFF,
    0x557FFFFF,
    0x555FFFFF,
    0x5557FFFF,
    0x5555FFFF,
    0x55557FFF,
    0x55555FFF,
    0x555557FF,
    0x555555FF,
    0x5555557F,
    0x5555555F,
    0x55555557,
    0x55555557,
    0x55555557,
    0x55555557,
    0x55555557,
    0x55555557,
    0x55555557,
    0x55555557,
    0x55555557,
    0x55555557,
    0x55555557,
    0x55555557,
    0x55555557,
    0x55555557,
    0x55555557,
    0x55555557,
    0x55555557,
    0x55555557,
};

/*
void precomp()
{
	unsigned int bitmaps[1024];

	int num = 0;

	printf("const static uint s_bitmapTableCTX[704] =\n{\n");

	for (int a = 1; a <= 15; a++)
	{
		  for (int b = a; b <= 15; b++)
		  {
				for (int c = b; c <= 15; c++)
				{
					int indices[16];

					int i = 0;
					for(; i < a; i++) {
						indices[i] = 0;
					}
					for(; i < a+b; i++) {
						indices[i] = 2;
					}
					for(; i < a+b+c; i++) {
						indices[i] = 3;
					}
					for(; i < 16; i++) {
						indices[i] = 1;
					}

					unsigned int bm = 0;
					for(i = 0; i < 16; i++) {
						bm |= indices[i] << (i * 2);
					}

					printf("\t0x%8X, // %d %d %d %d\n", bm, a-0, b-a, c-b, 16-c);

					bitmaps[num] = bm;
					num++;
				}
		  }
	}

	// Align to 32: 680 -> 704
	while (num < 704)
	{
		printf("\t0x80000000,\n");

		bitmaps[num] = 0x80000000; // 15 0 0 1;
		num++;
	}

	printf("}; // num = %d\n", num);
}
*/

const static uint s_bitmapTableCTX[704] = {
    0x55555578,   // 1 0 0 15
    0x555555F8,   // 1 0 1 14
    0x555557F8,   // 1 0 2 13
    0x55555FF8,   // 1 0 3 12
    0x55557FF8,   // 1 0 4 11
    0x5555FFF8,   // 1 0 5 10
    0x5557FFF8,   // 1 0 6 9
    0x555FFFF8,   // 1 0 7 8
    0x557FFFF8,   // 1 0 8 7
    0x55FFFFF8,   // 1 0 9 6
    0x57FFFFF8,   // 1 0 10 5
    0x5FFFFFF8,   // 1 0 11 4
    0x7FFFFFF8,   // 1 0 12 3
    0xFFFFFFF8,   // 1 0 13 2
    0xFFFFFFF8,   // 1 0 14 1
    0x555557E8,   // 1 1 0 14
    0x55555FE8,   // 1 1 1 13
    0x55557FE8,   // 1 1 2 12
    0x5555FFE8,   // 1 1 3 11
    0x5557FFE8,   // 1 1 4 10
    0x555FFFE8,   // 1 1 5 9
    0x557FFFE8,   // 1 1 6 8
    0x55FFFFE8,   // 1 1 7 7
    0x57FFFFE8,   // 1 1 8 6
    0x5FFFFFE8,   // 1 1 9 5
    0x7FFFFFE8,   // 1 1 10 4
    0xFFFFFFE8,   // 1 1 11 3
    0xFFFFFFE8,   // 1 1 12 2
    0xFFFFFFE8,   // 1 1 13 1
    0x55557FA8,   // 1 2 0 13
    0x5555FFA8,   // 1 2 1 12
    0x5557FFA8,   // 1 2 2 11
    0x555FFFA8,   // 1 2 3 10
    0x557FFFA8,   // 1 2 4 9
    0x55FFFFA8,   // 1 2 5 8
    0x57FFFFA8,   // 1 2 6 7
    0x5FFFFFA8,   // 1 2 7 6
    0x7FFFFFA8,   // 1 2 8 5
    0xFFFFFFA8,   // 1 2 9 4
    0xFFFFFFA8,   // 1 2 10 3
    0xFFFFFFA8,   // 1 2 11 2
    0xFFFFFFA8,   // 1 2 12 1
    0x5557FEA8,   // 1 3 0 12
    0x555FFEA8,   // 1 3 1 11
    0x557FFEA8,   // 1 3 2 10
    0x55FFFEA8,   // 1 3 3 9
    0x57FFFEA8,   // 1 3 4 8
    0x5FFFFEA8,   // 1 3 5 7
    0x7FFFFEA8,   // 1 3 6 6
    0xFFFFFEA8,   // 1 3 7 5
    0xFFFFFEA8,   // 1 3 8 4
    0xFFFFFEA8,   // 1 3 9 3
    0xFFFFFEA8,   // 1 3 10 2
    0xFFFFFEA8,   // 1 3 11 1
    0x557FFAA8,   // 1 4 0 11
    0x55FFFAA8,   // 1 4 1 10
    0x57FFFAA8,   // 1 4 2 9
    0x5FFFFAA8,   // 1 4 3 8
    0x7FFFFAA8,   // 1 4 4 7
    0xFFFFFAA8,   // 1 4 5 6
    0xFFFFFAA8,   // 1 4 6 5
    0xFFFFFAA8,   // 1 4 7 4
    0xFFFFFAA8,   // 1 4 8 3
    0xFFFFFAA8,   // 1 4 9 2
    0xFFFFFAA8,   // 1 4 10 1
    0x57FFEAA8,   // 1 5 0 10
    0x5FFFEAA8,   // 1 5 1 9
    0x7FFFEAA8,   // 1 5 2 8
    0xFFFFEAA8,   // 1 5 3 7
    0xFFFFEAA8,   // 1 5 4 6
    0xFFFFEAA8,   // 1 5 5 5
    0xFFFFEAA8,   // 1 5 6 4
    0xFFFFEAA8,   // 1 5 7 3
    0xFFFFEAA8,   // 1 5 8 2
    0xFFFFEAA8,   // 1 5 9 1
    0x7FFFAAA8,   // 1 6 0 9
    0xFFFFAAA8,   // 1 6 1 8
    0xFFFFAAA8,   // 1 6 2 7
    0xFFFFAAA8,   // 1 6 3 6
    0xFFFFAAA8,   // 1 6 4 5
    0xFFFFAAA8,   // 1 6 5 4
    0xFFFFAAA8,   // 1 6 6 3
    0xFFFFAAA8,   // 1 6 7 2
    0xFFFFAAA8,   // 1 6 8 1
    0xFFFEAAA8,   // 1 7 0 8
    0xFFFEAAA8,   // 1 7 1 7
    0xFFFEAAA8,   // 1 7 2 6
    0xFFFEAAA8,   // 1 7 3 5
    0xFFFEAAA8,   // 1 7 4 4
    0xFFFEAAA8,   // 1 7 5 3
    0xFFFEAAA8,   // 1 7 6 2
    0xFFFEAAA8,   // 1 7 7 1
    0xFFFAAAA8,   // 1 8 0 7
    0xFFFAAAA8,   // 1 8 1 6
    0xFFFAAAA8,   // 1 8 2 5
    0xFFFAAAA8,   // 1 8 3 4
    0xFFFAAAA8,   // 1 8 4 3
    0xFFFAAAA8,   // 1 8 5 2
    0xFFFAAAA8,   // 1 8 6 1
    0xFFEAAAA8,   // 1 9 0 6
    0xFFEAAAA8,   // 1 9 1 5
    0xFFEAAAA8,   // 1 9 2 4
    0xFFEAAAA8,   // 1 9 3 3
    0xFFEAAAA8,   // 1 9 4 2
    0xFFEAAAA8,   // 1 9 5 1
    0xFFAAAAA8,   // 1 10 0 5
    0xFFAAAAA8,   // 1 10 1 4
    0xFFAAAAA8,   // 1 10 2 3
    0xFFAAAAA8,   // 1 10 3 2
    0xFFAAAAA8,   // 1 10 4 1
    0xFEAAAAA8,   // 1 11 0 4
    0xFEAAAAA8,   // 1 11 1 3
    0xFEAAAAA8,   // 1 11 2 2
    0xFEAAAAA8,   // 1 11 3 1
    0xFAAAAAA8,   // 1 12 0 3
    0xFAAAAAA8,   // 1 12 1 2
    0xFAAAAAA8,   // 1 12 2 1
    0xEAAAAAA8,   // 1 13 0 2
    0xEAAAAAA8,   // 1 13 1 1
    0xAAAAAAA8,   // 1 14 0 1
    0x55555FA0,   // 2 0 0 14
    0x55557FA0,   // 2 0 1 13
    0x5555FFA0,   // 2 0 2 12
    0x5557FFA0,   // 2 0 3 11
    0x555FFFA0,   // 2 0 4 10
    0x557FFFA0,   // 2 0 5 9
    0x55FFFFA0,   // 2 0 6 8
    0x57FFFFA0,   // 2 0 7 7
    0x5FFFFFA0,   // 2 0 8 6
    0x7FFFFFA0,   // 2 0 9 5
    0xFFFFFFA0,   // 2 0 10 4
    0xFFFFFFA0,   // 2 0 11 3
    0xFFFFFFA0,   // 2 0 12 2
    0xFFFFFFA0,   // 2 0 13 1
    0x5555FEA0,   // 2 1 0 13
    0x5557FEA0,   // 2 1 1 12
    0x555FFEA0,   // 2 1 2 11
    0x557FFEA0,   // 2 1 3 10
    0x55FFFEA0,   // 2 1 4 9
    0x57FFFEA0,   // 2 1 5 8
    0x5FFFFEA0,   // 2 1 6 7
    0x7FFFFEA0,   // 2 1 7 6
    0xFFFFFEA0,   // 2 1 8 5
    0xFFFFFEA0,   // 2 1 9 4
    0xFFFFFEA0,   // 2 1 10 3
    0xFFFFFEA0,   // 2 1 11 2
    0xFFFFFEA0,   // 2 1 12 1
    0x555FFAA0,   // 2 2 0 12
    0x557FFAA0,   // 2 2 1 11
    0x55FFFAA0,   // 2 2 2 10
    0x57FFFAA0,   // 2 2 3 9
    0x5FFFFAA0,   // 2 2 4 8
    0x7FFFFAA0,   // 2 2 5 7
    0xFFFFFAA0,   // 2 2 6 6
    0xFFFFFAA0,   // 2 2 7 5
    0xFFFFFAA0,   // 2 2 8 4
    0xFFFFFAA0,   // 2 2 9 3
    0xFFFFFAA0,   // 2 2 10 2
    0xFFFFFAA0,   // 2 2 11 1
    0x55FFEAA0,   // 2 3 0 11
    0x57FFEAA0,   // 2 3 1 10
    0x5FFFEAA0,   // 2 3 2 9
    0x7FFFEAA0,   // 2 3 3 8
    0xFFFFEAA0,   // 2 3 4 7
    0xFFFFEAA0,   // 2 3 5 6
    0xFFFFEAA0,   // 2 3 6 5
    0xFFFFEAA0,   // 2 3 7 4
    0xFFFFEAA0,   // 2 3 8 3
    0xFFFFEAA0,   // 2 3 9 2
    0xFFFFEAA0,   // 2 3 10 1
    0x5FFFAAA0,   // 2 4 0 10
    0x7FFFAAA0,   // 2 4 1 9
    0xFFFFAAA0,   // 2 4 2 8
    0xFFFFAAA0,   // 2 4 3 7
    0xFFFFAAA0,   // 2 4 4 6
    0xFFFFAAA0,   // 2 4 5 5
    0xFFFFAAA0,   // 2 4 6 4
    0xFFFFAAA0,   // 2 4 7 3
    0xFFFFAAA0,   // 2 4 8 2
    0xFFFFAAA0,   // 2 4 9 1
    0xFFFEAAA0,   // 2 5 0 9
    0xFFFEAAA0,   // 2 5 1 8
    0xFFFEAAA0,   // 2 5 2 7
    0xFFFEAAA0,   // 2 5 3 6
    0xFFFEAAA0,   // 2 5 4 5
    0xFFFEAAA0,   // 2 5 5 4
    0xFFFEAAA0,   // 2 5 6 3
    0xFFFEAAA0,   // 2 5 7 2
    0xFFFEAAA0,   // 2 5 8 1
    0xFFFAAAA0,   // 2 6 0 8
    0xFFFAAAA0,   // 2 6 1 7
    0xFFFAAAA0,   // 2 6 2 6
    0xFFFAAAA0,   // 2 6 3 5
    0xFFFAAAA0,   // 2 6 4 4
    0xFFFAAAA0,   // 2 6 5 3
    0xFFFAAAA0,   // 2 6 6 2
    0xFFFAAAA0,   // 2 6 7 1
    0xFFEAAAA0,   // 2 7 0 7
    0xFFEAAAA0,   // 2 7 1 6
    0xFFEAAAA0,   // 2 7 2 5
    0xFFEAAAA0,   // 2 7 3 4
    0xFFEAAAA0,   // 2 7 4 3
    0xFFEAAAA0,   // 2 7 5 2
    0xFFEAAAA0,   // 2 7 6 1
    0xFFAAAAA0,   // 2 8 0 6
    0xFFAAAAA0,   // 2 8 1 5
    0xFFAAAAA0,   // 2 8 2 4
    0xFFAAAAA0,   // 2 8 3 3
    0xFFAAAAA0,   // 2 8 4 2
    0xFFAAAAA0,   // 2 8 5 1
    0xFEAAAAA0,   // 2 9 0 5
    0xFEAAAAA0,   // 2 9 1 4
    0xFEAAAAA0,   // 2 9 2 3
    0xFEAAAAA0,   // 2 9 3 2
    0xFEAAAAA0,   // 2 9 4 1
    0xFAAAAAA0,   // 2 10 0 4
    0xFAAAAAA0,   // 2 10 1 3
    0xFAAAAAA0,   // 2 10 2 2
    0xFAAAAAA0,   // 2 10 3 1
    0xEAAAAAA0,   // 2 11 0 3
    0xEAAAAAA0,   // 2 11 1 2
    0xEAAAAAA0,   // 2 11 2 1
    0xAAAAAAA0,   // 2 12 0 2
    0xAAAAAAA0,   // 2 12 1 1
    0xAAAAAAA0,   // 2 13 0 1
    0x5557FA80,   // 3 0 0 13
    0x555FFA80,   // 3 0 1 12
    0x557FFA80,   // 3 0 2 11
    0x55FFFA80,   // 3 0 3 10
    0x57FFFA80,   // 3 0 4 9
    0x5FFFFA80,   // 3 0 5 8
    0x7FFFFA80,   // 3 0 6 7
    0xFFFFFA80,   // 3 0 7 6
    0xFFFFFA80,   // 3 0 8 5
    0xFFFFFA80,   // 3 0 9 4
    0xFFFFFA80,   // 3 0 10 3
    0xFFFFFA80,   // 3 0 11 2
    0xFFFFFA80,   // 3 0 12 1
    0x557FEA80,   // 3 1 0 12
    0x55FFEA80,   // 3 1 1 11
    0x57FFEA80,   // 3 1 2 10
    0x5FFFEA80,   // 3 1 3 9
    0x7FFFEA80,   // 3 1 4 8
    0xFFFFEA80,   // 3 1 5 7
    0xFFFFEA80,   // 3 1 6 6
    0xFFFFEA80,   // 3 1 7 5
    0xFFFFEA80,   // 3 1 8 4
    0xFFFFEA80,   // 3 1 9 3
    0xFFFFEA80,   // 3 1 10 2
    0xFFFFEA80,   // 3 1 11 1
    0x57FFAA80,   // 3 2 0 11
    0x5FFFAA80,   // 3 2 1 10
    0x7FFFAA80,   // 3 2 2 9
    0xFFFFAA80,   // 3 2 3 8
    0xFFFFAA80,   // 3 2 4 7
    0xFFFFAA80,   // 3 2 5 6
    0xFFFFAA80,   // 3 2 6 5
    0xFFFFAA80,   // 3 2 7 4
    0xFFFFAA80,   // 3 2 8 3
    0xFFFFAA80,   // 3 2 9 2
    0xFFFFAA80,   // 3 2 10 1
    0x7FFEAA80,   // 3 3 0 10
    0xFFFEAA80,   // 3 3 1 9
    0xFFFEAA80,   // 3 3 2 8
    0xFFFEAA80,   // 3 3 3 7
    0xFFFEAA80,   // 3 3 4 6
    0xFFFEAA80,   // 3 3 5 5
    0xFFFEAA80,   // 3 3 6 4
    0xFFFEAA80,   // 3 3 7 3
    0xFFFEAA80,   // 3 3 8 2
    0xFFFEAA80,   // 3 3 9 1
    0xFFFAAA80,   // 3 4 0 9
    0xFFFAAA80,   // 3 4 1 8
    0xFFFAAA80,   // 3 4 2 7
    0xFFFAAA80,   // 3 4 3 6
    0xFFFAAA80,   // 3 4 4 5
    0xFFFAAA80,   // 3 4 5 4
    0xFFFAAA80,   // 3 4 6 3
    0xFFFAAA80,   // 3 4 7 2
    0xFFFAAA80,   // 3 4 8 1
    0xFFEAAA80,   // 3 5 0 8
    0xFFEAAA80,   // 3 5 1 7
    0xFFEAAA80,   // 3 5 2 6
    0xFFEAAA80,   // 3 5 3 5
    0xFFEAAA80,   // 3 5 4 4
    0xFFEAAA80,   // 3 5 5 3
    0xFFEAAA80,   // 3 5 6 2
    0xFFEAAA80,   // 3 5 7 1
    0xFFAAAA80,   // 3 6 0 7
    0xFFAAAA80,   // 3 6 1 6
    0xFFAAAA80,   // 3 6 2 5
    0xFFAAAA80,   // 3 6 3 4
    0xFFAAAA80,   // 3 6 4 3
    0xFFAAAA80,   // 3 6 5 2
    0xFFAAAA80,   // 3 6 6 1
    0xFEAAAA80,   // 3 7 0 6
    0xFEAAAA80,   // 3 7 1 5
    0xFEAAAA80,   // 3 7 2 4
    0xFEAAAA80,   // 3 7 3 3
    0xFEAAAA80,   // 3 7 4 2
    0xFEAAAA80,   // 3 7 5 1
    0xFAAAAA80,   // 3 8 0 5
    0xFAAAAA80,   // 3 8 1 4
    0xFAAAAA80,   // 3 8 2 3
    0xFAAAAA80,   // 3 8 3 2
    0xFAAAAA80,   // 3 8 4 1
    0xEAAAAA80,   // 3 9 0 4
    0xEAAAAA80,   // 3 9 1 3
    0xEAAAAA80,   // 3 9 2 2
    0xEAAAAA80,   // 3 9 3 1
    0xAAAAAA80,   // 3 10 0 3
    0xAAAAAA80,   // 3 10 1 2
    0xAAAAAA80,   // 3 10 2 1
    0xAAAAAA80,   // 3 11 0 2
    0xAAAAAA80,   // 3 11 1 1
    0xAAAAAA80,   // 3 12 0 1
    0x55FFAA00,   // 4 0 0 12
    0x57FFAA00,   // 4 0 1 11
    0x5FFFAA00,   // 4 0 2 10
    0x7FFFAA00,   // 4 0 3 9
    0xFFFFAA00,   // 4 0 4 8
    0xFFFFAA00,   // 4 0 5 7
    0xFFFFAA00,   // 4 0 6 6
    0xFFFFAA00,   // 4 0 7 5
    0xFFFFAA00,   // 4 0 8 4
    0xFFFFAA00,   // 4 0 9 3
    0xFFFFAA00,   // 4 0 10 2
    0xFFFFAA00,   // 4 0 11 1
    0x5FFEAA00,   // 4 1 0 11
    0x7FFEAA00,   // 4 1 1 10
    0xFFFEAA00,   // 4 1 2 9
    0xFFFEAA00,   // 4 1 3 8
    0xFFFEAA00,   // 4 1 4 7
    0xFFFEAA00,   // 4 1 5 6
    0xFFFEAA00,   // 4 1 6 5
    0xFFFEAA00,   // 4 1 7 4
    0xFFFEAA00,   // 4 1 8 3
    0xFFFEAA00,   // 4 1 9 2
    0xFFFEAA00,   // 4 1 10 1
    0xFFFAAA00,   // 4 2 0 10
    0xFFFAAA00,   // 4 2 1 9
    0xFFFAAA00,   // 4 2 2 8
    0xFFFAAA00,   // 4 2 3 7
    0xFFFAAA00,   // 4 2 4 6
    0xFFFAAA00,   // 4 2 5 5
    0xFFFAAA00,   // 4 2 6 4
    0xFFFAAA00,   // 4 2 7 3
    0xFFFAAA00,   // 4 2 8 2
    0xFFFAAA00,   // 4 2 9 1
    0xFFEAAA00,   // 4 3 0 9
    0xFFEAAA00,   // 4 3 1 8
    0xFFEAAA00,   // 4 3 2 7
    0xFFEAAA00,   // 4 3 3 6
    0xFFEAAA00,   // 4 3 4 5
    0xFFEAAA00,   // 4 3 5 4
    0xFFEAAA00,   // 4 3 6 3
    0xFFEAAA00,   // 4 3 7 2
    0xFFEAAA00,   // 4 3 8 1
    0xFFAAAA00,   // 4 4 0 8
    0xFFAAAA00,   // 4 4 1 7
    0xFFAAAA00,   // 4 4 2 6
    0xFFAAAA00,   // 4 4 3 5
    0xFFAAAA00,   // 4 4 4 4
    0xFFAAAA00,   // 4 4 5 3
    0xFFAAAA00,   // 4 4 6 2
    0xFFAAAA00,   // 4 4 7 1
    0xFEAAAA00,   // 4 5 0 7
    0xFEAAAA00,   // 4 5 1 6
    0xFEAAAA00,   // 4 5 2 5
    0xFEAAAA00,   // 4 5 3 4
    0xFEAAAA00,   // 4 5 4 3
    0xFEAAAA00,   // 4 5 5 2
    0xFEAAAA00,   // 4 5 6 1
    0xFAAAAA00,   // 4 6 0 6
    0xFAAAAA00,   // 4 6 1 5
    0xFAAAAA00,   // 4 6 2 4
    0xFAAAAA00,   // 4 6 3 3
    0xFAAAAA00,   // 4 6 4 2
    0xFAAAAA00,   // 4 6 5 1
    0xEAAAAA00,   // 4 7 0 5
    0xEAAAAA00,   // 4 7 1 4
    0xEAAAAA00,   // 4 7 2 3
    0xEAAAAA00,   // 4 7 3 2
    0xEAAAAA00,   // 4 7 4 1
    0xAAAAAA00,   // 4 8 0 4
    0xAAAAAA00,   // 4 8 1 3
    0xAAAAAA00,   // 4 8 2 2
    0xAAAAAA00,   // 4 8 3 1
    0xAAAAAA00,   // 4 9 0 3
    0xAAAAAA00,   // 4 9 1 2
    0xAAAAAA00,   // 4 9 2 1
    0xAAAAAA00,   // 4 10 0 2
    0xAAAAAA00,   // 4 10 1 1
    0xAAAAAA00,   // 4 11 0 1
    0x7FFAA800,   // 5 0 0 11
    0xFFFAA800,   // 5 0 1 10
    0xFFFAA800,   // 5 0 2 9
    0xFFFAA800,   // 5 0 3 8
    0xFFFAA800,   // 5 0 4 7
    0xFFFAA800,   // 5 0 5 6
    0xFFFAA800,   // 5 0 6 5
    0xFFFAA800,   // 5 0 7 4
    0xFFFAA800,   // 5 0 8 3
    0xFFFAA800,   // 5 0 9 2
    0xFFFAA800,   // 5 0 10 1
    0xFFEAA800,   // 5 1 0 10
    0xFFEAA800,   // 5 1 1 9
    0xFFEAA800,   // 5 1 2 8
    0xFFEAA800,   // 5 1 3 7
    0xFFEAA800,   // 5 1 4 6
    0xFFEAA800,   // 5 1 5 5
    0xFFEAA800,   // 5 1 6 4
    0xFFEAA800,   // 5 1 7 3
    0xFFEAA800,   // 5 1 8 2
    0xFFEAA800,   // 5 1 9 1
    0xFFAAA800,   // 5 2 0 9
    0xFFAAA800,   // 5 2 1 8
    0xFFAAA800,   // 5 2 2 7
    0xFFAAA800,   // 5 2 3 6
    0xFFAAA800,   // 5 2 4 5
    0xFFAAA800,   // 5 2 5 4
    0xFFAAA800,   // 5 2 6 3
    0xFFAAA800,   // 5 2 7 2
    0xFFAAA800,   // 5 2 8 1
    0xFEAAA800,   // 5 3 0 8
    0xFEAAA800,   // 5 3 1 7
    0xFEAAA800,   // 5 3 2 6
    0xFEAAA800,   // 5 3 3 5
    0xFEAAA800,   // 5 3 4 4
    0xFEAAA800,   // 5 3 5 3
    0xFEAAA800,   // 5 3 6 2
    0xFEAAA800,   // 5 3 7 1
    0xFAAAA800,   // 5 4 0 7
    0xFAAAA800,   // 5 4 1 6
    0xFAAAA800,   // 5 4 2 5
    0xFAAAA800,   // 5 4 3 4
    0xFAAAA800,   // 5 4 4 3
    0xFAAAA800,   // 5 4 5 2
    0xFAAAA800,   // 5 4 6 1
    0xEAAAA800,   // 5 5 0 6
    0xEAAAA800,   // 5 5 1 5
    0xEAAAA800,   // 5 5 2 4
    0xEAAAA800,   // 5 5 3 3
    0xEAAAA800,   // 5 5 4 2
    0xEAAAA800,   // 5 5 5 1
    0xAAAAA800,   // 5 6 0 5
    0xAAAAA800,   // 5 6 1 4
    0xAAAAA800,   // 5 6 2 3
    0xAAAAA800,   // 5 6 3 2
    0xAAAAA800,   // 5 6 4 1
    0xAAAAA800,   // 5 7 0 4
    0xAAAAA800,   // 5 7 1 3
    0xAAAAA800,   // 5 7 2 2
    0xAAAAA800,   // 5 7 3 1
    0xAAAAA800,   // 5 8 0 3
    0xAAAAA800,   // 5 8 1 2
    0xAAAAA800,   // 5 8 2 1
    0xAAAAA800,   // 5 9 0 2
    0xAAAAA800,   // 5 9 1 1
    0xAAAAA800,   // 5 10 0 1
    0xFFAAA000,   // 6 0 0 10
    0xFFAAA000,   // 6 0 1 9
    0xFFAAA000,   // 6 0 2 8
    0xFFAAA000,   // 6 0 3 7
    0xFFAAA000,   // 6 0 4 6
    0xFFAAA000,   // 6 0 5 5
    0xFFAAA000,   // 6 0 6 4
    0xFFAAA000,   // 6 0 7 3
    0xFFAAA000,   // 6 0 8 2
    0xFFAAA000,   // 6 0 9 1
    0xFEAAA000,   // 6 1 0 9
    0xFEAAA000,   // 6 1 1 8
    0xFEAAA000,   // 6 1 2 7
    0xFEAAA000,   // 6 1 3 6
    0xFEAAA000,   // 6 1 4 5
    0xFEAAA000,   // 6 1 5 4
    0xFEAAA000,   // 6 1 6 3
    0xFEAAA000,   // 6 1 7 2
    0xFEAAA000,   // 6 1 8 1
    0xFAAAA000,   // 6 2 0 8
    0xFAAAA000,   // 6 2 1 7
    0xFAAAA000,   // 6 2 2 6
    0xFAAAA000,   // 6 2 3 5
    0xFAAAA000,   // 6 2 4 4
    0xFAAAA000,   // 6 2 5 3
    0xFAAAA000,   // 6 2 6 2
    0xFAAAA000,   // 6 2 7 1
    0xEAAAA000,   // 6 3 0 7
    0xEAAAA000,   // 6 3 1 6
    0xEAAAA000,   // 6 3 2 5
    0xEAAAA000,   // 6 3 3 4
    0xEAAAA000,   // 6 3 4 3
    0xEAAAA000,   // 6 3 5 2
    0xEAAAA000,   // 6 3 6 1
    0xAAAAA000,   // 6 4 0 6
    0xAAAAA000,   // 6 4 1 5
    0xAAAAA000,   // 6 4 2 4
    0xAAAAA000,   // 6 4 3 3
    0xAAAAA000,   // 6 4 4 2
    0xAAAAA000,   // 6 4 5 1
    0xAAAAA000,   // 6 5 0 5
    0xAAAAA000,   // 6 5 1 4
    0xAAAAA000,   // 6 5 2 3
    0xAAAAA000,   // 6 5 3 2
    0xAAAAA000,   // 6 5 4 1
    0xAAAAA000,   // 6 6 0 4
    0xAAAAA000,   // 6 6 1 3
    0xAAAAA000,   // 6 6 2 2
    0xAAAAA000,   // 6 6 3 1
    0xAAAAA000,   // 6 7 0 3
    0xAAAAA000,   // 6 7 1 2
    0xAAAAA000,   // 6 7 2 1
    0xAAAAA000,   // 6 8 0 2
    0xAAAAA000,   // 6 8 1 1
    0xAAAAA000,   // 6 9 0 1
    0xFAAA8000,   // 7 0 0 9
    0xFAAA8000,   // 7 0 1 8
    0xFAAA8000,   // 7 0 2 7
    0xFAAA8000,   // 7 0 3 6
    0xFAAA8000,   // 7 0 4 5
    0xFAAA8000,   // 7 0 5 4
    0xFAAA8000,   // 7 0 6 3
    0xFAAA8000,   // 7 0 7 2
    0xFAAA8000,   // 7 0 8 1
    0xEAAA8000,   // 7 1 0 8
    0xEAAA8000,   // 7 1 1 7
    0xEAAA8000,   // 7 1 2 6
    0xEAAA8000,   // 7 1 3 5
    0xEAAA8000,   // 7 1 4 4
    0xEAAA8000,   // 7 1 5 3
    0xEAAA8000,   // 7 1 6 2
    0xEAAA8000,   // 7 1 7 1
    0xAAAA8000,   // 7 2 0 7
    0xAAAA8000,   // 7 2 1 6
    0xAAAA8000,   // 7 2 2 5
    0xAAAA8000,   // 7 2 3 4
    0xAAAA8000,   // 7 2 4 3
    0xAAAA8000,   // 7 2 5 2
    0xAAAA8000,   // 7 2 6 1
    0xAAAA8000,   // 7 3 0 6
    0xAAAA8000,   // 7 3 1 5
    0xAAAA8000,   // 7 3 2 4
    0xAAAA8000,   // 7 3 3 3
    0xAAAA8000,   // 7 3 4 2
    0xAAAA8000,   // 7 3 5 1
    0xAAAA8000,   // 7 4 0 5
    0xAAAA8000,   // 7 4 1 4
    0xAAAA8000,   // 7 4 2 3
    0xAAAA8000,   // 7 4 3 2
    0xAAAA8000,   // 7 4 4 1
    0xAAAA8000,   // 7 5 0 4
    0xAAAA8000,   // 7 5 1 3
    0xAAAA8000,   // 7 5 2 2
    0xAAAA8000,   // 7 5 3 1
    0xAAAA8000,   // 7 6 0 3
    0xAAAA8000,   // 7 6 1 2
    0xAAAA8000,   // 7 6 2 1
    0xAAAA8000,   // 7 7 0 2
    0xAAAA8000,   // 7 7 1 1
    0xAAAA8000,   // 7 8 0 1
    0xAAAA0000,   // 8 0 0 8
    0xAAAA0000,   // 8 0 1 7
    0xAAAA0000,   // 8 0 2 6
    0xAAAA0000,   // 8 0 3 5
    0xAAAA0000,   // 8 0 4 4
    0xAAAA0000,   // 8 0 5 3
    0xAAAA0000,   // 8 0 6 2
    0xAAAA0000,   // 8 0 7 1
    0xAAAA0000,   // 8 1 0 7
    0xAAAA0000,   // 8 1 1 6
    0xAAAA0000,   // 8 1 2 5
    0xAAAA0000,   // 8 1 3 4
    0xAAAA0000,   // 8 1 4 3
    0xAAAA0000,   // 8 1 5 2
    0xAAAA0000,   // 8 1 6 1
    0xAAAA0000,   // 8 2 0 6
    0xAAAA0000,   // 8 2 1 5
    0xAAAA0000,   // 8 2 2 4
    0xAAAA0000,   // 8 2 3 3
    0xAAAA0000,   // 8 2 4 2
    0xAAAA0000,   // 8 2 5 1
    0xAAAA0000,   // 8 3 0 5
    0xAAAA0000,   // 8 3 1 4
    0xAAAA0000,   // 8 3 2 3
    0xAAAA0000,   // 8 3 3 2
    0xAAAA0000,   // 8 3 4 1
    0xAAAA0000,   // 8 4 0 4
    0xAAAA0000,   // 8 4 1 3
    0xAAAA0000,   // 8 4 2 2
    0xAAAA0000,   // 8 4 3 1
    0xAAAA0000,   // 8 5 0 3
    0xAAAA0000,   // 8 5 1 2
    0xAAAA0000,   // 8 5 2 1
    0xAAAA0000,   // 8 6 0 2
    0xAAAA0000,   // 8 6 1 1
    0xAAAA0000,   // 8 7 0 1
    0xAAA80000,   // 9 0 0 7
    0xAAA80000,   // 9 0 1 6
    0xAAA80000,   // 9 0 2 5
    0xAAA80000,   // 9 0 3 4
    0xAAA80000,   // 9 0 4 3
    0xAAA80000,   // 9 0 5 2
    0xAAA80000,   // 9 0 6 1
    0xAAA80000,   // 9 1 0 6
    0xAAA80000,   // 9 1 1 5
    0xAAA80000,   // 9 1 2 4
    0xAAA80000,   // 9 1 3 3
    0xAAA80000,   // 9 1 4 2
    0xAAA80000,   // 9 1 5 1
    0xAAA80000,   // 9 2 0 5
    0xAAA80000,   // 9 2 1 4
    0xAAA80000,   // 9 2 2 3
    0xAAA80000,   // 9 2 3 2
    0xAAA80000,   // 9 2 4 1
    0xAAA80000,   // 9 3 0 4
    0xAAA80000,   // 9 3 1 3
    0xAAA80000,   // 9 3 2 2
    0xAAA80000,   // 9 3 3 1
    0xAAA80000,   // 9 4 0 3
    0xAAA80000,   // 9 4 1 2
    0xAAA80000,   // 9 4 2 1
    0xAAA80000,   // 9 5 0 2
    0xAAA80000,   // 9 5 1 1
    0xAAA80000,   // 9 6 0 1
    0xAAA00000,   // 10 0 0 6
    0xAAA00000,   // 10 0 1 5
    0xAAA00000,   // 10 0 2 4
    0xAAA00000,   // 10 0 3 3
    0xAAA00000,   // 10 0 4 2
    0xAAA00000,   // 10 0 5 1
    0xAAA00000,   // 10 1 0 5
    0xAAA00000,   // 10 1 1 4
    0xAAA00000,   // 10 1 2 3
    0xAAA00000,   // 10 1 3 2
    0xAAA00000,   // 10 1 4 1
    0xAAA00000,   // 10 2 0 4
    0xAAA00000,   // 10 2 1 3
    0xAAA00000,   // 10 2 2 2
    0xAAA00000,   // 10 2 3 1
    0xAAA00000,   // 10 3 0 3
    0xAAA00000,   // 10 3 1 2
    0xAAA00000,   // 10 3 2 1
    0xAAA00000,   // 10 4 0 2
    0xAAA00000,   // 10 4 1 1
    0xAAA00000,   // 10 5 0 1
    0xAA800000,   // 11 0 0 5
    0xAA800000,   // 11 0 1 4
    0xAA800000,   // 11 0 2 3
    0xAA800000,   // 11 0 3 2
    0xAA800000,   // 11 0 4 1
    0xAA800000,   // 11 1 0 4
    0xAA800000,   // 11 1 1 3
    0xAA800000,   // 11 1 2 2
    0xAA800000,   // 11 1 3 1
    0xAA800000,   // 11 2 0 3
    0xAA800000,   // 11 2 1 2
    0xAA800000,   // 11 2 2 1
    0xAA800000,   // 11 3 0 2
    0xAA800000,   // 11 3 1 1
    0xAA800000,   // 11 4 0 1
    0xAA000000,   // 12 0 0 4
    0xAA000000,   // 12 0 1 3
    0xAA000000,   // 12 0 2 2
    0xAA000000,   // 12 0 3 1
    0xAA000000,   // 12 1 0 3
    0xAA000000,   // 12 1 1 2
    0xAA000000,   // 12 1 2 1
    0xAA000000,   // 12 2 0 2
    0xAA000000,   // 12 2 1 1
    0xAA000000,   // 12 3 0 1
    0xA8000000,   // 13 0 0 3
    0xA8000000,   // 13 0 1 2
    0xA8000000,   // 13 0 2 1
    0xA8000000,   // 13 1 0 2
    0xA8000000,   // 13 1 1 1
    0xA8000000,   // 13 2 0 1
    0xA0000000,   // 14 0 0 2
    0xA0000000,   // 14 0 1 1
    0xA0000000,   // 14 1 0 1
    0x80000000,   // 15 0 0 1
    0x80000000,
    0x80000000,
    0x80000000,
    0x80000000,
    0x80000000,
    0x80000000,
    0x80000000,
    0x80000000,
    0x80000000,
    0x80000000,
    0x80000000,
    0x80000000,
    0x80000000,
    0x80000000,
    0x80000000,
    0x80000000,
    0x80000000,
    0x80000000,
    0x80000000,
    0x80000000,
    0x80000000,
    0x80000000,
    0x80000000,
    0x80000000,
};
