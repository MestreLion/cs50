// Custom scripts. Requires jQuery (not included in this file)

var BASE_YEAR = 2019;

function year_range()
{
	var year = (new Date()).getFullYear();
	if (year <= BASE_YEAR)
		return year;
	return BASE_YEAR + '-' + year;
}

$(document).ready(function() {
	$("#copyright_year").text(year_range());
});
