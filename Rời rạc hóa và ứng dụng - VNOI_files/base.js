// This file should be loaded for all pages after JS libraries and before all other scripts.

// HELPER METHODS

// String interpolation method
// Usage:
// "I'm {age} years old!".supplant({ age: 29 });
// "The {a} says {n}, {n}, {n}!".supplant({ a: 'cow', n: 'moo' });
// "The {0} says {1}, {1}, {1}!".supplant(['cow', 'moo'])
String.prototype.supplant = function (o) {
    return this.replace(/{([^{}]*)}/g,
        function (a, b) {
            var r = o[b];
            return typeof r === 'string' || typeof r === 'number' ? r : a;
        }
    );
};

function showNotification(message) {
	$.jGrowl(message, {
		position: 'bottom-right'
	});
}
// END OF HELPER METHODS



// CONSTANT DECLARATIONS
var VOTING_URL = "/forum/vote/{post_id}/?type={vote_type}";
// END OF CONSTANT DECLARATIONS



// METHODS THAT SHOULD BE COMMON TO ALL PAGES
function voteSuccess(post_id, type) {
	var otherButtonId = (type == 'd' ? 'upvote' : 'downvote') + '-' + post_id;
	var buttonId = (type == 'u' ? 'upvote' : 'downvote') + '-' + post_id;
	$('#' + buttonId).attr('disabled', true);
	$('#' + buttonId).addClass('voted');
	$('#' + otherButtonId).hide();
}

$(document).ready(function () {
	$('[data-toggle="offcanvas"]').click(function () {
		$('.row-offcanvas').toggleClass('active')
	});

	// Handling clicking on up-vote / down-vote. Since these elements are shown in home page + forum topic retrieve
	// page, I'm putting these methods here.

	function changeVote(type) {
		return function () {
			var clickedElement = $(this);
			var postId = clickedElement.attr('post-id');
			var totalVoteElement = $("#total-vote-{post_id}".supplant({post_id: postId}));
			var currentVote = parseInt(totalVoteElement.text(), 10);

			$.ajax({
				url: VOTING_URL.supplant({
					post_id: postId,
					vote_type: type
				}),
				success: function (data) {
					showNotification(data['message']);
					if (data['success'] == 1) {
						if (type == 'u') {
							totalVoteElement.text(currentVote + 1);
							voteSuccess(postId, 'u')
						}
						else {
							totalVoteElement.text(currentVote - 1);
							voteSuccess(postId, 'd');
						}
					}
				},
				error: function (data) {
					showNotification('Bạn cần phải đăng nhập trước.');
				},
				dataType: 'json'
			});
		}
	}
	$('.post-upvote').click(changeVote('u'));
	$('.post-downvote').click(changeVote('d'));
	$('.home-post-upvote').click(changeVote('u'));
	$('.home-post-downvote').click(changeVote('d'));
});
