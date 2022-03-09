// Copyright (C) 2004-2021 Artifex Software, Inc.
//
// This file is part of MuPDF.
//
// MuPDF is free software: you can redistribute it and/or modify it under the
// terms of the GNU Affero General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// MuPDF is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more
// details.
//
// You should have received a copy of the GNU Affero General Public License
// along with MuPDF. If not, see <https://www.gnu.org/licenses/agpl-3.0.en.html>
//
// Alternative licensing terms are available from the licensor.
// For commercial licensing, see <https://www.artifex.com/> or contact
// Artifex Software, Inc., 1305 Grant Avenue - Suite 200, Novato,
// CA 94945, U.S.A., +1(415)492-9861, for further information.

#include "mupdf/fitz.h"

fz_outline *
fz_new_outline(fz_context *ctx)
{
	fz_outline *outline = fz_malloc_struct(ctx, fz_outline);
	outline->refs = 1;
	return outline;
}

fz_outline *
fz_keep_outline(fz_context *ctx, fz_outline *outline)
{
	return fz_keep_imp(ctx, outline, &outline->refs);
}

void
fz_drop_outline(fz_context *ctx, fz_outline *outline)
{
	while (fz_drop_imp(ctx, outline, &outline->refs))
	{
		fz_outline *next = outline->next;
		fz_drop_outline(ctx, outline->down);
		fz_free(ctx, outline->title);
		fz_free(ctx, outline->uri);
		fz_free(ctx, outline);
		outline = next;
	}
}