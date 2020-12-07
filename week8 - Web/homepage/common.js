// Custom scripts. Requires jQuery (not included in this file)

function year_range(base_year)
{
	var year = (new Date()).getFullYear();
	if (year <= base_year)
		return year;
	return base_year + '-' + year;
}

$(document).ready(function() {
	$("#copyright_year").text(year_range($("#copyright_year").text()));
});
